namespace MyList
{
	template<class T>
	struct ListNode //节点类
	{
		ListNode(const T& val = T())
			: _pPrev(nullptr)
			, _pNext(nullptr)
			, _val(val)
		{}

		ListNode* _pPrev;
		ListNode* _pNext;
		T _val;
	};

	template<class T, class Ref, class Ptr>
	class Iterator //迭代器类
	{
		typedef ListNode<T>* __pNode;
		typedef Iterator<T, Ref, Ptr> _Self;

	public:
		Iterator(__pNode pNode = nullptr) //迭代器类构造函数
			: _pNode(pNode)
		{}

		Iterator(const _Self& self)//拷贝构造
		{
			_pNode = self._pNode;
		}

		Ref operator*() //重载迭代器,使 *it 可行
		{
			return _pNode->_val; 
		}

		Ptr operator->() //重载 -> ,使 it-> 得到的是val的地址
		{
			return &_pNode->_val;
		}

		_Self& operator++() //重载前置++ ,使 ++it
		{
			_pNode = _pNode->_pNext;
			return *this;
		}

		_Self operator++(int) //重载后置++ ,使 it++ 并返回 it 
		{
			_Self tmp = *this;
			_pNode = _pNode->_pNext;
			return tmp;
		}

		_Self& operator--() //重载前置--, 使 --it
		{
			_pNode = _pNode->_pPrev;
			return *this;
		}

		_Self operator--(int) //重载后置-- ,使 it-- 并返回 it 
		{
			_Self tmp = _pNode; //隐式转换
			_pNode = _pNode->_pPrev;
			return tmp;
		}

		bool operator!=(const _Self& self)
		{
			return _pNode != self._pNode;
		}

		bool operator==(const _Self& self)
		{
			return _pNode == self._pNode;
		}

	public:
		__pNode _pNode;
	};

	template<class T>
	class List //List类
	{
		typedef ListNode<T> Node;
		typedef Node* pNode;
		typedef size_t size_type;

	public:
		typedef Iterator<T, T&, T*> iterator;
		typedef Iterator<T, const T&, const T*> const_iterator;

		void empty_init()
		{
			_pHead = new Node;
			_pHead->_pNext = _pHead;
			_pHead->_pPrev = _pHead;
		}

		List() //无参构造
		{
			empty_init();
		}

		List(int n, const T& val = T())//有参构造
		{
			empty_init();
			for (int i = 0; i < n; i++)
			{
				insert(end(), val);
			}
		}

		template<class Iterator>
		List(Iterator first, Iterator end) //有参构造
		{
			empty_init();
			while (first != end)
			{
				push_back(*first);
				++first;
			}
		}

		List(const List& self) //拷贝构造
		{
			empty_init();
			for (auto& e : self)
			{
				push_back(e);
			}
		}

		List& operator=(List& list) //重载 = 
		{
			swap(list);
			return *this;
		}

		~List()  //析构函数
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
			_Lsize = 0;
		}

		iterator begin()
		{
			return _pHead->_pNext; //返回的是pNode 类型,存在隐式转换将pNode 转换成 iterator
		}

		iterator end()
		{
			return _pHead;
		}

		const_iterator begin() const
		{
			return _pHead->_pNext;
		}

		const_iterator end() const
		{
			return _pHead;
		}

		iterator insert(iterator it, const T& val)
		{
			pNode cur = it._pNode; //备份
			pNode prev = cur->_pPrev; //备份前一个元素
			pNode newNode = new Node(val); //新建节点
			prev->_pNext = newNode;
			newNode->_pNext = cur;
			newNode->_pPrev = prev;
			cur->_pPrev = newNode;
			_Lsize++;
			return newNode;
		}

		iterator erase(iterator it)
		{
			if (it == end()) return 0;
			pNode del = it._pNode;
			pNode prev = del->_pPrev;
			pNode next = del->_pNext;
			delete del;
			prev->_pNext = next;
			next->_pPrev = prev;
			_Lsize--;
			return next;
		}

		void push_back(const T& val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		void swap(List<T>& list)
		{
			std::swap(_pHead, list._pHead);
			std::swap(_Lsize, list._Lsize);
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
			_Lsize = 0;
		}

		size_type size() const
		{
			return _Lsize;
		}

		bool empty() const
		{
			return _Lsize == 0;
		}

		T& front()
		{
			return _pHead->_pNext->_val;
		}

		const T& front() const
		{
			return _pHead->_pNext->_val;
		}

		T& back()
		{
			return _pHead->_pPrev->_val;
		}
		
		const T& back() const
		{
			return _pHead->_pPrev->_val;
		}

	private:
		pNode _pHead;
		size_type _Lsize;
	};
}
