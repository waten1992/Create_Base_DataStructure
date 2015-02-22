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
	BinarySearchTree():root(NULL){}
	BinarySearchTree(const BinarySearchTree &rhs):root(NULL)//构造函数
	{
		*this = rhs;
	}
	~BinarySearchTree() //析构
	{
		MakeEmpty();
	}

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

void Insert(const Comparable & x , BinaryNode *& t)
{
	if ( t == NULL )
		t = new BinaryNode(x , NULL ,NULL);
	else if(x < t->element)
		Insert(x,t->left);
	else if( x , t->element)
		Insert(x,t->right);
	else
		;
}
/*
remove(const Comparable &x , BinaryNode *&t)
递归版本：
低估出口：
		if ( t == NULL ) return ;
递归条件：
		大于KEY 去右子树找 
		小于KEY 去左子树找
		等于KEY 
				1-是叶子节点 ，直接删除
				2-有2个子树时，找到当前节点的右子树的最小孩子代替当前节点，
				再次调用Remove(),删除右孩子最小节点
----------------------------------------------------

*/
void Remove(const Comparable &x , BinaryNode *& t)
{
	if ( t == NULL )
		return ;
	if ( x < t->element )
		Remove(x , t->left);
	else if (x > t->element)
		Remove(x , t->right);
	else if (t->left != NULL && t->right != NULL) //有2个孩子节点时，先要找到右子树的最小孩子代替当前元素，然后在调用Remove()
	{
		t->element = FindMin(t->right)->element;//找到右子树的最小孩子代替当前元素
		Remove(t->element,t->right);//再次调用Remove()
	}
	else // 当只有左子树 或者  右子树 的时候
	{
		BinaryNode *OldNode = t ; 
		t = (t->left != NULL) ? t->left : t->right ; //若左子节点不为空，直接指向左子树。同理右子树也一样
		delete OldNode ;
	}
}
/*析构函数*/
~BinarySearchTree()
{
	MakeEmpty();
}

void MakeEmpty (BinaryNode * &t)
{
	if(t != NULL)
	{
		MakeEmpty(t->left);
		MakeEmpty(t->right);
		delete t ;
	}
	t = NULL ; //指向空节点；
}
/* Deep copy */
const BinarySearchTree &operator= (const BinaryNode *& rhs)
{
	if (this != &rhs)
	{
		MakeEmpty();
		root = clone(rhs.root);
	}
	return *this ;
}
/*  */
BinaryNode *clone (BinaryNode *t) const
{
	if (t == NULL)
		return NULL;
	return new BinaryNode(t->element , clone(t->left) ,clone(t->right));
}

void printTree( BinaryNode *t, ostream & out ) const //中序遍历
    {
        if( t != NULL )
        {
            PrintTree( t->left, out );
            out << t->element << endl;
            PrintTree( t->right, out );
        }
    }