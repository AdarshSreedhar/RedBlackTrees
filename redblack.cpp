#include<iostream>
#include<string>
using namespace std;
template<typename T>
struct node
{
	T key;
	//int value;
	int color;
	node<T> *parent;
	node<T> *left;
	node<T> *right;	
	
	node<T> *operator++();
    node<T> *operator++(int);
    node<T> *operator--();
    node<T> *operator--(int);
};
template<typename T, typename op>
class RBtree
{	private:
			node<T> *root = NULL;
	public:
			void insertNode(T,op pred);
			void insertFix(node<T> *p);
			void rotateRight(node<T>*);
			void rotateLeft(node<T>*);
			void rrCase(node<T>*);
			void llCase(node<T>*);
			void display(node<T>*);
			void disp();
			void displayReverse();
			void displayInorder();
			void deleteNode(T,op pred);
			
			void deleteFix(node<T>*);
			void inorderNode(node<T>*);
			
			void coloralternate(int);
			void changecolor(int,int);
			void finddifference();
			node<T>* minValueNode(node<T>*);
			node<T>* maxValueNode(node<T>*);
			node<T>* inOrderSuccessor(node<T>*,op);
			node<T>* inOrderPredecessor(node<T>*,op);
			node<T>* search(T,op pred);
			/*class MyIterator
			{	
				private :
					bool leftOver = false;
					node<T> *it;
					node<T> *root;
				MyIterator(node<T> *p = NULL): it(p),root(p){}
				MyIterator& operator++()
				{
					if(it->left!=NULL && !leftOver)
						it = it->left;
					if(it->left == NULL)
					{
						leftOver = true;
					}
					else
					{	/*if(it->parent!=NULL)
						{	it = it->parent;
							if(it->right!=NULL)
							{	
								it = it->right;
								break;
							}
						}
						it = it -> parent;
						if(it!=root)
						{
							while(it->right==NULL)
							{
								it = it->parent;
							}
							it = it->right;
						}
						else
						{
							if(it == root)
							{
								leftOver = false;
							}
						}
						
					}
					
					return *this;
				}
				
				bool operator==(const MyIterator& rhs) const
				{
					return it == rhs;
				}
				bool operator!=(const MyIterator& rhs) const
				{
				//	return p_it_ != rhs.p_it_;
					return !(*this	== rhs);
				}
			};
				MyIterator begin()
				{
					return new MyIterator(root);
				}
				MyIterator end()
				{
					return new MyIterator();
				}*/
			
			
};

template<typename T, typename op>
void RBtree<T,op>::insertNode(T key,op pred)
{
	node<T> *newnode = new node<T>;
	newnode->key = key;
	
	if(root == NULL)
	{
		root = newnode;
		root->parent = NULL;
		root->left = NULL;
		root->right = NULL;
		root->color = 0;
	}
	else
	{	node<T> *p = root;
		node<T> *q = NULL;
		while(p!=NULL)
		{	
			int res = pred(key,p->key);
			if(res==-1)
			{	q = p;
				p=p->left;
			}
			else
			{	q = p;
				p=p->right;
			}
		}
		if(q->key > newnode->key)
		{
			q->left = newnode;
		}
		else
		{
			q->right = newnode;
		}
		newnode->parent = q;
		newnode->left = NULL;
		newnode->right = NULL;
		newnode->color = 0;
	}
	insertFix(newnode);
}

template<typename T, typename op>
void RBtree<T,op>::insertFix(node<T> *p)
{	if(p->parent !=NULL)
	while(p!=root && p->parent->color!=0)
	{	int temp = 0;node<T> *n;
		if(p->parent->parent !=NULL)
		{
			node<T> *parentNode = p->parent;
			node<T> *gpNode = p->parent->parent;
			if(gpNode->right == parentNode)
			{
				if(gpNode->left !=NULL && gpNode->left->color == 1)
				{
					parentNode->color = 0;
					gpNode->left->color = 0;
					gpNode->color = 1;
					p = gpNode;
				}
				else
				{	if(p->color!=0)
					{if(parentNode->left == p)
					{
						rotateRight(parentNode);
						rrCase(p->parent);
						n = p->parent;
					}
					else
					{
						rrCase(gpNode);
						n = gpNode;
					}
					temp = n->parent->color;
					n->parent->color = n->color;
					n->color = temp;
				}
				}
			}
			else
			{
				if(gpNode->right !=NULL && gpNode->right->color == 1)
				{
					parentNode->color = 0;
					gpNode->right->color = 0;
					gpNode->color = 1;
					p = gpNode;
				}
				else
				{	if(p->color!=0)
					{if(parentNode->left == p)
					{	
					
						llCase(gpNode);
						n = gpNode;
					}
					else
					{	
						rotateLeft(parentNode);
						llCase(p->parent);
						n = p->parent;
					}
					temp = n->parent->color;
					n->parent->color = n->color;
					n->color = temp;
				}
				}
			}
		}
	}
	if(p == root)
	{
		p->color = 0;
	}
}
template<typename T, typename op>
void RBtree<T,op>::disp()
{
	display(root);
}

/*template<typename ptr_t,typename T,typename op>
void dispUsingIt(ptr_t first,ptr_t last,RBtree<T,op> *t)
{
	while(first!=last)
	{
		t.display(first);
		++first;
	}
}*/

template<typename T, typename op>
void RBtree<T,op>::displayReverse()
{	
	//cout<< "sadaadfs\n";
	node<T> *first = maxValueNode(root);
	node<T> *tempOne= new node<T>;
	tempOne->key = first->key;
	node<T> *last = minValueNode(root);
	//cout<< first->key << last->key << "\n";
	
	while(first->key != last->key)
    {
        //cout << first << last << "\n";
        cout << first->key << " ";
        	(*first)--;
        //cout << "while"<< "\n";
    }
    cout << first->key << " ";
    first->key = tempOne->key;
}

template<typename T, typename op>
void RBtree<T,op>::displayInorder()
{
	node<T> *first = minValueNode(root);
	node<T> *tempOne= new node<T>;
	tempOne->key = first->key;
	node<T> *last = maxValueNode(root);

	while(first->key != last->key)
    {
        //cout << first << last << "\n";
        cout << first->key << " ";
        	(*first)++;
        //cout << "while"<< "\n";
    }
    cout << first->key << " ";
    first->key = tempOne->key;
}

template<typename T, typename op>
void RBtree<T,op>::display(node<T> *p)
{
	//node<T> *p = root;
	if(root==NULL)
     {
          cout<<"\nEmpty Tree.";
          return ;
     }
     if(p!=NULL)
     {	//cout << root->key <<"\n";
                cout<<"\n\t NODE: ";
                cout<<"\n Key: "<<p->key;
                cout<<"\n Colour: ";
    if(p->color==0)
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->key;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->key;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->key;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;
    if(p->left)
    {
                 cout<<"\n\nLeft:\n";
     display(p->left);
    }
    /*else
     cout<<"\nNo Left Child.\n";*/
    if(p->right)
    {
     cout<<"\n\nRight:\n";
                 display(p->right);
    }
    /*else
     cout<<"\nNo Right Child.\n"*/
    // cout << "faskjakjskaj"<< "\n";
	/*node<T> *first = minValueNode(root);
	cout << root->key <<"\n";
	//cout << "faskjakjskaj"<< "\n";
    //cout << first->key << " ";
    node<T> *last = maxValueNode(root);
    //cout << "faskjakjskaj"<< "\n";
    
    while(first->key != last->key)
    {
        //cout << first << last << "\n";
        cout << first->key << " ";
        	(*first)++;
        //cout << "while"<< "\n";
    }
    cout << last->key << " ";
    
   /*node<T> *last = minValueNode(root);
    node<T> *first = maxValueNode(root);
    cout << (root->right->key) << "\n";
    //cout << "Pred:" << "\n";
    //cout << first->key << " ";
    while(first->key != last->key)
    {
    	cout << first->key << " ";
        	(*first)--;
        	//cout << "while"<< "\n";
    }
    cout << last->key << " ";*/

	}
}

template<typename T,typename op>
node<T>* RBtree<T,op>::search(T key, op pred)
{
	node<T> *p=root;
	while(p!=NULL)
	{	
		int res = pred(key,p->key);
		if(res==-1)
		{	
			p=p->left;
		}
		else
		{	if(res==1)
				p=p->right;
			else
				return p;
		}
		 
	}
	return NULL;
}


template<typename T, typename op>
void RBtree<T,op>::llCase(node<T> *n)
{
	n->left->parent = n->parent;
	if(n->parent!=NULL)
	{	if(n->parent->right == n)
			n->parent->right = n->left;
		else
			n->parent->left = n->left;
	}
	n->parent = n->left;
	n->left = n->parent->right;
	if(n->left!=NULL)
		n->left->parent = n;
	n->parent->right = n;
	node<T> *f = n->parent;
	while(f->parent!=NULL)
	{
		f = f->parent;
	}
	root = f;
	
	/*int temp = n->parent->color;
	n->parent->color = n->color;
	n->color = temp;*/
}
template<typename T, typename op>
void RBtree<T,op>::rrCase(node<T> *n)
{
	n->right->parent = n->parent;
	if(n->parent!=NULL)
	{	if(n->parent->right == n)
			n->parent->right = n->right;
		else
			n->parent->left = n->right;
	}
	n->parent = n->right;
	n->right = n->parent->left;
	if(n->right!=NULL)
		n->right->parent = n;
	n->parent->left = n;
	node<T> *f = n->parent;
	while(f->parent!=NULL)
	{
		f = f->parent;
	}
	root = f;
	
	/*int temp = n->parent->color;
	n->parent->color = n->color;
	n->color = temp;*/
}
template<typename T, typename op>
void RBtree<T,op>::rotateLeft(node<T> *n)
{
	n->right->parent = n->parent;
	n->parent->left = n->right;
	n->right = n->right->left;
	n->parent->left->left = n;
	n->parent= n->parent->left;
}
template<typename T, typename op>
void RBtree<T,op>::rotateRight(node<T> *n)
{
	n->left->parent = n->parent;
	n->parent->right = n->left;
	n->left = n->left->right;
	n->parent->right->right = n;
	n->parent = n->parent->right;
}
template<typename T, typename op>
void RBtree<T,op>::deleteNode(T key,op pred)
{
	if(root==NULL)
	{
		cout<<"Empty tree!"<<endl;
	}
	else
	{	node<T> *p = root;
		//cout << "wlfl"<<endl;
		while(p!=NULL)
		{	
			int res = pred(key,p->key);
			if(res==-1)
			{
				p=p->left;
			}
			else
			{	if(res==0)
					break;
				else
					p=p->right;
			}
			
		}
		//cout << "wlfl"<<endl;
		if(p==root && (p->left==NULL && p->right == NULL))
			p = root = NULL;
		if(p!=NULL)
		deleteFix(p);
	}
}
template<typename T, typename op>
void RBtree<T,op>::deleteFix(node<T> *n)
{	bool deleted = false; 
	// use deleted variable for not deleting simply.
	if(n->left!=NULL || n->right!=NULL)
	{	
		
		int sibcolor = 0,makecolor = 0;
		if(n!=root)
		{	
		if(n->parent->left == n) 
			{ 
				if(n->parent->right!=NULL)
					sibcolor = n->parent->right->color;
				else
					{
						if(n->parent->left!=NULL)
							sibcolor = n->parent->left->color;
						else
							{
								makecolor = 1;
							}
					}
			}
		}
		
		
		inorderNode(n);
		cout << "wlfl"<<endl;
		if(n->right != NULL && n->left != NULL)
		{
				n->color = sibcolor;
		}
		else
		{
			n->color = 0;
			if(makecolor == 1)
			{
				n->color = 1;
			}
		}
		// use rotation properly.
		//recolour
	}
	else
	{	node<T> *temp;
		/*if(n->left!=NULL)
		{
			if(n->color == 1 || n->left->color == 1)
			{
					temp = n->left;
					temp->color = 0;
					temp->parent = n->parent;
					if(temp->parent!=NULL)
					temp->parent->left = temp;
					n->parent = NULL;
					n->left = NULL;
					n = temp;
					deleted = true;
			}
		}
		else
		{	if(n->right!=NULL)
			{
				if(n->color == 1 || n->right->color == 1)
				{
						temp = n->right;
						temp->color = 0;
						temp->parent = n->parent;
						if(n->parent!=NULL)
						{
							if(n->parent->left == n)
							{
								n->parent->left = temp;
							}
							else
							{
								n->parent->right = temp;
							}
						}
						//if(temp->parent!=NULL)
						//temp->parent->right = temp;
						n->parent = NULL;
						n->right = NULL;
						cout << "fjafjahf\n";
						n = temp;
						deleted = true;
				}
			}
			else
			{*/
				if(n->color == 1)
				{	
					if(n->parent->left == n)
						n->parent->left = NULL;
					if(n->parent->right == n)
						n->parent->right = NULL;
					temp = n->parent;
					n->parent = NULL;
					n = root;
					deleted = true;
				}
			//}
		//}
		if(n==root)
			root = n;

		while(n!=root && n->color == 0)
		{
			if(n->color == 0)
			{int temp = 0;
			if(n->left==NULL && n->right==NULL)
			{
				//if(n->color==0 && n!=root)
				//{
					if(n->parent->left == n)
					{
						node<T> *sib = n->parent->right;
						cout << sib->key << "\n";
						if(((sib->left!=NULL && sib->left->color==1) && (sib->right!=NULL && sib->right->color==1)) || (sib->right!=NULL && sib->right->color==1) && !deleted)
						{
							n->parent->left = NULL;
							n->parent = NULL;
							rrCase(sib->parent);
							cout << sib->key <<"\n";	
							sib->right->color = sib->color;
							n = sib;
						}
						else
						{
							if((sib->left!=NULL && sib->left->color==1) && !deleted)
							{
								n->parent->left = NULL;
								n->parent = NULL;
								rotateRight(sib);
								sib->color = 0;
								rrCase(sib->parent->parent);
								n = sib;
							}
							else
							{
								if(((sib->left!=NULL && sib->left->color==0) && (sib->right!=NULL && sib->right->color==0)))
								{
									//sib->right = 1;
									//recolour
									if(!deleted)
									{
										/*then delete*/
										cout << "Delete now L" <<"\n";
										if(n->parent->right == n)
											n->parent->right = NULL;
										else
											n->parent->left = NULL;
										n->parent = NULL;
									}
									int sibcolor = 0,makecolor = 0;
									if(n!=root)
									{	
									if(n->parent->left == n) 
										{ 
											if(n->parent->right!=NULL)
												sibcolor = n->parent->right->color;
											else
												{
													if(n->parent->left!=NULL)
														sibcolor = n->parent->left->color;
													else
														{
															makecolor = 1;
														}
												}
										}
									}
									if(sib->right != NULL && sib->left != NULL)
									{
										sib->color = sibcolor;
									}
									else
									{
										sib->color = 0;
										if(makecolor == 1)
										{
											n->color = 1;
										}
									}
									cout<< "Recolour" <<"\n";
									n = root;
								}
								else
								{
									if(sib->left==NULL && sib->right==NULL)
									{	
										//recolor
										if(!deleted)
										{
											/*then delete*/
											cout << "Delete now L1" <<"\n";
											if(n->parent->right == n)
												n->parent->right = NULL;
											else
												n->parent->left = NULL;
										}
										
										int sibcolor = 0,makecolor = 0;
										if(n!=root)
										{	
										if(n->parent->left == n) 
											{ 
												if(n->parent->right!=NULL)
													sibcolor = n->parent->right->color;
												else
													{
														if(n->parent->left!=NULL)
															sibcolor = n->parent->left->color;
														else
															{
																makecolor = 1;
															}
													}
											}
										}
										
										if(sib->right != NULL && sib->left != NULL)
										{
											sib->color = sibcolor;
										}
										else
										{
											sib->color = 0;
											if(makecolor == 1)
											{
												sib->color = 1;
											}
										}
										n = root;
										cout<< "Recolour" <<"\n";
									}
								}
								if(sib->color == 1 && !deleted)
								{
									rrCase(sib->parent);
									n = sib;
									temp = n->color;
									n->color = n->left->color;
									n->left->color = temp;
								}
							}
						}
					}
					else
					{
						node<T> *sib = n->parent->left;
						if(((sib->left!=NULL && sib->left->color==1) && (sib->right!=NULL && sib->right->color==1)) || (sib->left!=NULL && sib->left->color==1) && !deleted)
						{	
							n->parent->right = NULL;
							n->parent = NULL;
							llCase(sib->parent);
							sib->left->color = sib->color;
							n = sib;
						}
						else
						{
							if((sib->right!=NULL && sib->right->color==1) && !deleted)
							{
								n->parent->right = NULL;
								n->parent = NULL;
								rotateLeft(sib);
								sib->color = 0;
								llCase(sib->parent->parent);
								n = sib;
							}
							else
							{
								if(((sib->left!=NULL && sib->left->color==0) && (sib->right!=NULL && sib->right->color==0)))
								{
									//sib->right = 1;
									//recolour
									if(!deleted)
									{
										/*then delete*/
										cout << "Delete now R" <<"\n";
										if(n->parent->right == n)
											n->parent->right = NULL;
										else
											n->parent->left = NULL;
										n->parent = NULL;
									}
									
									int sibcolor = 0,makecolor = 0;
									if(n!=root)
									{	
									if(n->parent->left == n) 
										{ 
											if(n->parent->right!=NULL)
												sibcolor = n->parent->right->color;
											else
												{
													if(n->parent->left!=NULL)
														sibcolor = n->parent->left->color;
													else
														{
															makecolor = 1;
														}
												}
										}
									}
									
									if(sib->right != NULL && sib->left != NULL)
									{
										sib->color = sibcolor;
									}
									else
									{
										sib->color = 0;
										if(makecolor == 1)
										{
											n->color = 1;
										}
									}
									
									cout<< "Recolour" <<"\n";
									n = root;
								}
								else
								{
									if(sib->left==NULL && sib->right==NULL)
									{	
										
										if(!deleted)
										{
											/*then delete*/
											cout << "Delete now R1" <<"\n";
											if(n->parent->right == n)
												n->parent->right = NULL;
											else
												n->parent->left = NULL;
											n->parent = NULL;
										}
										// recolouring
										int sibcolor = 0,makecolor = 0;
										if(n!=root)
										{	
										if(n->parent->left == n) 
											{ 
												if(n->parent->right!=NULL)
													sibcolor = n->parent->right->color;
												else
													{
														if(n->parent->left!=NULL)
															sibcolor = n->parent->left->color;
														else
															{
																makecolor = 1;
															}
													}
											}
										}
										
										if(sib->right != NULL && sib->left != NULL)
										{
											sib->color = sibcolor;
										}
										else
										{
											sib->color = 0;
											if(makecolor == 1)
											{
												n->color = 1;
											}
										}
										
										cout<< "Recolour" <<"\n";
										n = root;
									}
								}
								if(sib->color == 1 && !deleted)
								{
									llCase(sib->parent);
									n = sib;
									temp = n->color;
									n->color = n->right->color;
									n->right->color = temp;
								}
							}
						}
					}
			}

		}

		/*if(n->color == 1 && n!=root)
			{	if(n->left!=NULL || n->right!=NULL)
				{
					if(n->right == NULL)
					{
						node *temp = n->left;
						if(temp->color==1)
						{
							temp->parent = n->parent;
							temp->parent->left = temp;
							n->parent = NULL;
							n->left = NULL;
						}
						else
						{
				
						}
					}
					else
					{
						node *temp = n->right;
						if(temp->color==1)
						{
							temp->parent = n->parent;
							temp->parent->right = temp;
							n->parent = NULL;
							n->right = NULL;
						}
					}
				}
				else
				{
			
				}
			}*/
		}
	}
	//cout << "here:" << "\n";
	if(n==root)
	{	
		cout << "here:" << "\n";
		root->color = 0;
	}
}
template<typename T,typename op>
void RBtree<T,op>::finddifference()
{
	int countofleftsubtree=1;
	int countofrightsubtree=1;
	node<T> *t=root;
	do
	{
		++countofleftsubtree;
		t=t->left;
	}
	while(t!=NULL);
	node<T>* u=root;
	do
	{
		++countofrightsubtree;
		u=u->right;
	}
	while(u!=NULL);

	cout<<"difference:"<<(countofleftsubtree-countofrightsubtree)<<endl;
	changecolor(countofleftsubtree,countofrightsubtree);

}

template<typename T,typename op>
void RBtree<T,op>::changecolor(int countofleftsubtree,int countofrightsubtree)
{	
	//cout<<"hoii"<<countofrightsubtree<<countofleftsubtree<<endl;
	node<T> *i=root;
	//cout<<"jijij\n";
	if(countofrightsubtree>countofleftsubtree)
	{	
		//cout<<"mew\n";
		int maxnoblacknodes=countofrightsubtree/2;
		cout<<countofleftsubtree<<maxnoblacknodes<<"\n";
		if(countofleftsubtree>maxnoblacknodes)
		{
			int diff=countofleftsubtree-maxnoblacknodes;
			i=root->left;
			while(diff&&i->left!=NULL)
			{
				i=i->left;
				i->color=1;
				if(i->left!=NULL)
					i=i->left;
				--diff;
			}
			/*while(i->color==1)
				i=i->left;
			i->color=1;
			/*1 means right*/
			coloralternate(1);
		}
		else if(countofleftsubtree==maxnoblacknodes)
		{
			coloralternate(1);
		}
	}
	else if(countofleftsubtree>countofrightsubtree)
	{
		int maxnoblacknodes=countofleftsubtree/2;
		if(countofrightsubtree>maxnoblacknodes)
		{
			int diff=countofrightsubtree-maxnoblacknodes;
			//cout<<"meowmeo\n";
			i=root->right;
			while(diff&&i->right!=NULL)
			{
				i=i->right;
				i->color=1;
				if(i->right!=NULL)
					i=i->right;
				--diff;
			}
			/*while(i->color!=1)
				i=i->right;
			if(i!=NULL)
				i->color=1;
			/*1 means right*/
			coloralternate(0);
		}
		else if(countofleftsubtree==maxnoblacknodes)
		{
			coloralternate(0);
		}
	}
}
template<typename T,typename op>
void RBtree<T,op>::coloralternate(int s)
{
	//cout<<"hi\n";
	node<T>* a;
	if(s==1)
	{
		a=root;
		while(a->right!=NULL)
		{
			a=a->right;
			a->color=1;
			if(a->right!=NULL)
				a=a->right;
		}
	}
	else if(s==0)
	{

		a=root;
		while(a->left!=NULL)
		{
			a=a->left;
			a->color=1;
			if(a->left!=NULL)
				a=a->left;
		}
	}
	
}
template<typename T, typename op>
void RBtree<T,op>::inorderNode(node<T> *n)
{
			node<T> *t;
			//inorder
			if(n->left!=NULL)
			{	
				t = n->left;
				while(t->right!=NULL)
				{
					t = t->right;
				}
				
			}
			else
			{
				t = n->right;
				while(t->left!=NULL)
				{
					t = t->left;
				}
				
			}
			/*if(t->left!=NULL)
				t->left = n->left;
			else
			{
				t->left = NULL;
			}
			if(t->right!=NULL)
				t->right = n->right;
			else
			{
				t->right = NULL;
			}*/
			cout << "wlflfahgfjsaj"<<endl;
			if(t->parent->left == t)
			{	
				t->parent->left = t->right;
				t->right = n->right;
				if(n->right!=NULL)
				n->right->parent = t;
				if(t->parent!=n)
				{
					t->left = n->left;
					if(n->left!=NULL)
					n->left->parent = t;
				}
				
			}	
			else
			{	
				t->parent->right = t->left;
				t->left = n->left;
				if(n->left!=NULL)
				n->left->parent = t;
				if(t->parent!=n)
				{
					t->right = n->right;
					if(n->right!=NULL)
					n->right->parent = t;
				}
				
			}
			cout << t->key << "\n";
			//cout << t->left->key << "\n";
			//cout << t->left->right->key << "\n";
			//cout << t->right->key << "\n";
			t->parent = n->parent;
			if(n!=root)
			{
				if(n->parent->left == n)
					n->parent->left = t;
				else
					n->parent->right = t;
			}
			else
				root = t;
			n->parent = NULL;
			n->left = NULL;
			n->right = NULL;
			//n = t;
			cout << t << "\t" << root << "\n";
			if(t==root)
			{	
				cout << "here:" << "\n";
				root->color = 0;
			}
			//cout << d <<"\n";				
}
/*template<typename T>
int compare_func(T key1,T key2)
{
	if(key1<key2)
		return -1;
	else
	{
		if(key1>key2)
			return 1;
		else
			return 0;	
	}
}
*/
template<typename T>
struct compare
{
	int operator()(T key1,T key2)
	{
		if(key1<key2)
		return -1;
		else
		{
			if(key1>key2)
				return 1;
			else
				return 0;	
		}
	}
};

RBtree<int,compare<int>> obj;

int main()
{	int ch;int y=0;
	
	int inskey;
	int delkey;
	node<int> *n;
	do
    {
                cout<<"\n\t RED BLACK TREE " ;
                cout<<"\n 1. Insert in the tree ";
                cout<<"\n 2. Delete a node from the tree";
                cout<<"\n 3. Search for an element in the tree";
                cout<<"\n 4. Display the tree";
                cout<<"\n 5. Display inorder";
                cout<<"\n 6. Display Reverse"; 
                cout<<"\n 7. Exit " ;
                cout<<"\n 8. Find difference of heights";
                cout<<"\nEnter Your Choice: ";
                cin>>ch;
                switch(ch)
                {
                          case 1 : 	
                          			cout<<"\nEnter key of the node to be inserted: ";
                          			cin >> inskey;
                          		   obj.insertNode(inskey,compare<int>());
                                   cout<<"\nNode Inserted.\n";
                                   break;
                          case 2 : 
                          			cout<<"\nEnter the key of the node to be deleted: ";
                          			cin >> delkey;
                          			obj.deleteNode(delkey,compare<int>());
                                   break;
                          case 3 : cout<<"\nenter element to be searched: ";
                          		   cin>>inskey;
                          		   //cout<<(obj.search(inskey,compare<int>()))->key<<endl;
                          		   n = obj.search(inskey,compare<int>());
                          		   if(n!=NULL)
                          		   {
                          		   	cout << n->key <<endl;
                          		   	if(n->color == 1)
                          		   		cout << "RED" <<endl;
                          		   	else
                          		   		cout << "BLACK" <<endl;
                          		   }
                                   break;
                          case 4 : 
                          			obj.disp();
                                   break;
                          case 5 : obj.displayInorder();
                          			break;
                          case 6 : obj.displayReverse();
                          			break;
                          case 7 : y=1;
                                   break;
                          case 8: obj.finddifference();         
                          default : cout<<"\nEnter a Valid Choice.";
                          			break;
                }
                cout<<endl;

    }while(y!=1);
	return 0;
}

template<typename T>
node<T>* node<T>::operator++()
{ // pre
                *this  =  *obj.inOrderSuccessor(this,compare<int>());
                return this;
}

template<typename T>
node<T>* node<T>::operator++(int)
{ // post
                node<T> *temp = this;
                ++(*this);
                return temp;
}

template<typename T,typename op>
node<T> *RBtree<T,op>::minValueNode(node<T> *n)
{
    node<T> *current = n;
     while (current->left != NULL)
        current = current->left;
    return current;
}

template<typename T,typename op>
node<T> *RBtree<T,op>::maxValueNode(node<T> *n)
{
    node<T> *current = n;
     while (current->right != NULL)
        current = current->right;
    return current;
}

template<typename T,typename op>
node<T> *RBtree<T,op>::inOrderSuccessor(node<T> *n,op func)
{
    // step 1 of the above algorithm
    node<T> *temp = root;
    if( n->right != NULL )
    {	//cout << "minval" << "\n";
        return minValueNode(n->right);
 	}
   	node<T> *succ = NULL;
 
    // Start from root and search for successor down the tree
    while (temp != NULL){
        if (func(n->key,temp->key)){
            succ = temp;
            temp = temp->left;
        }
        else if (n->key!=temp->key && !func(n->key,temp->key))
            temp = temp->right;
        else
           break;
    }
    return succ;
}

template<typename T>
node<T>* node<T>::operator--()
{ // pre
                *this  =  *obj.inOrderPredecessor(this,compare<int>());
                return this;
}

template<typename T>
node<T>* node<T>::operator--(int)
{ // post
                node<T> *temp = this;
                --(*this);
                return temp;
}

template<typename T,typename op>
node<T> *RBtree<T,op>::inOrderPredecessor(node<T> *n,op func)
{
    // step 1 of the above algorithm
    node<T> *temp = root;
    if( n->left != NULL )
    {	//cout << "minval" << "\n";
        return maxValueNode(n->left);
 	}
   	node<T> *pred = NULL;
 
    // Start from root and search for predecessor down the tree
    while (temp != NULL)
    {
        if (func(n->key,temp->key)){
            pred = temp;
            //temp = temp->right;
            //if(temp!=root)
            	//pred = temp -> parent;
            //cout << "right" << "\n";
            temp = temp -> right;
        }
        else if (n->key!=temp->key && !func(n->key,temp->key))
        {	//cout << "left" << "\n";
        	//pred = temp;
        	//temp = NULL;
            temp = temp->left;
        }
        else
        	{	//cout << "root" << "\n";
        		//pred = temp;
        		break;
        	}
           
    }
    return pred;
}
