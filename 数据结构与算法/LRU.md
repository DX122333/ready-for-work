# LRU
**【问题leetcode146】** 实现 LRUCache 类：
    LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
    int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
    void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
    函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
```
class LRUCache {
int m_capacity;
unordered_map<int, int> m_k2v;
list<int> m_kl;
unordered_map<int, list<int>::iterator> m_k2i;
public:
    LRUCache(int capacity):m_capacity(capacity) {

    }
    
    int get(int key) {
        auto it = m_k2v.find(key);
        if(it == m_k2v.end()){
            return -1;
        }

        auto l_it = m_k2i[key];
        m_kl.erase(l_it);
        m_kl.push_back(key);
        m_k2i[key] = --m_kl.end();

        return it->second;
    }
    
    void put(int key, int value) {
        auto it = m_k2v.find(key);
        if(it != m_k2v.end()){
            m_k2v[key] = value;
            get(key);
        }else{
            if(m_capacity == m_k2v.size()){
                auto del_key = *m_kl.begin();
                m_kl.pop_front();
                m_k2v.erase(del_key);
                m_k2i.erase(del_key);
            }

            m_k2v[key] = value;
            m_kl.push_back(key);
            m_k2i[key] = --m_kl.end();
        }
    }
};

```