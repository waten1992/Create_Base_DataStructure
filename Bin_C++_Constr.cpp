template <typename Comparable>
const Comparable & FindMax (const std::vector<Comparable> &v)
{
	int MaxIndex = 0 ;
	for (int i = 1 ; i < a.size() ; i++)
		if (a[MaxIndex] < a[i])
			MaxIndex = i ;
	return a[MaxIndex];
}





template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree(arguments);
	BinarySearchTree(const BinarySearchTree &rhs);
	~BinarySearchTree();

	const Comparable &FindMin() const ;
	const Comparable &FindMax() const ;
	bool Contains (const Comparable &x) cosnt ;
	void PrinTree() const;

	void MakeEmpty() ;
	void Insert(const Comparable &x);
	void Remove(const Comparable &x);
	
	const BinarySearchTree & operator= (const BinarySearchTree &rhs);
private:
	struct BinaryNode  
	{
		Comparable element ;
		BinaryNode * left ;
		BinaryNode * right ;
		BinaryNode (const Comparable &TheElement ,BinaryNode *Lt ,BinaryNode *Rt)
			:element(TheElement),left(Lt),right(Rt){}
	};
	BinaryNode *root ;

	void Insert(const Comparable &x , BinaryNode *&t) const ;
	void Remove(const Comparable &x , BinaryNode *&t) const ;
	BinaryNode * FindMax(BinaryNode *t) const ;
	BinaryNode * FindMin(BinaryNode *t) const ;
	bool Contains(const Comparable &x ,BinaryNode *t) const ;
	void MakeEmpty(BinaryNode *&t) ;
	void PrinTree(BinaryNode *t) const ;
	BinaryNode *clone (BinaryNode *t) const ;
};

#if 0
//公有函数调用私有成员函数；
bool Contains(const Comparable &x) const
{
	return Contains(x.root) ;
}

void Insert(const Comparable &x)
{
	Insert( x , root ) ;
} 
void Remove(const Comparable &x)
{
	Remove(x , root) ;
}
#endif

bool Contains (const Comparable &x , BinaryNode *t) const
{
	if(t == NULL)
		return false ;
	else if (x < t->element )
		return Contains(x , x->left) ;
	else if (x > t->element )
		return Contains(x , x->right);
	else
		return true ; //递归出口
} 


template <typename Object , typename Comparable = less <Object> >
class BinarySearchTree
{
public:
	 BinarySearchTree(arguments);
	~ BinarySearchTree();

private:
	BinaryNode *root ;
	Comparable isLessThan ;

bool Contains (const Comparable &x , BinaryNode *t) const
{
	if(t == NULL)
		return false ;
	else if (x < t->element )
		return Contains(x , x->left) ;
	else if (x > t->element )
		return Contains(x , x->right);
	else
		return true ; //递归出口
} 
	/* data */
};

BinaryNode * FindMin(BinaryNode *t) const //找到最左的左子树就好了
{
	if ( t == NULL )
		return NULL;
	if ( t->left == NULL )
		return t;
	return FindMin(t->left);
}
BinaryNode * FindMax(BinaryNode *t) const //找最右子树,非递归版本
{
	if (t == NULL)
		return NULL;
	while(t->right != NULL)
	{
		t = t->right;
	}
	return t;
}