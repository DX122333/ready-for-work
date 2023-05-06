```
#include <unordered_map>
#include <vector>
class Solution {
public:
    unordered_map<int, int> key2val; //键值队
    unordered_map<int, int> key2freq;   //键及其对应的频率
    map<int, list<int>> freq2dlist; //每个频率下的所有键
    unordered_map<int, list<int>::iterator> key2iter; //每个键所在的队列位置
    int capacity;

    int get(int key){
        //key未出现或已被移除，返回-1
        if(key2val.find(key)==key2val.end()) return -1;

        //获得key对应的频率
        int f = key2freq[key];
        //从对应频率的队列中删除该键
        freq2dlist[f].erase(key2iter[key]);
        if(freq2dlist[f].size()==0) freq2dlist.erase(f);
        ++f;
        key2freq[key] = f;
        freq2dlist[f].push_back(key);
        key2iter[key] = --freq2dlist[f].end();
        return key2val[key];
    }
    void set(int key, int val){
        if(capacity==0) return;
        if(key2val.find(key)!=key2val.end()){
            key2val[key] = val;
            get(key);
        }else{
            if(key2val.size()==capacity){
                //删除频率最小且调用最早
                auto it = freq2dlist.begin();
                auto k = it->second.front();
                it->second.pop_front();
                if(it->second.size()==0) freq2dlist.erase(it);
                key2iter.erase(k);
                key2freq.erase(k);
                key2val.erase(k);
            }

            key2val[key] = val;
            key2freq[key] = 1;
            freq2dlist[1].push_back(key);
            key2iter[key] = --freq2dlist[1].end();
        
        }
    }
    vector<int> LFU(vector<vector<int> >& operators, int k) {
        // write code here
        capacity = k;
        vector<int> ans;
        for(auto& i:operators){
            if(i[0]==1){
                set(i[1], i[2]);
            }else if(i[0]==2){
                int tmp = get(i[1]);
                ans.push_back(tmp);
            }
        }

        return ans;
    }
};
```

```
#include <unordered_map>
#include <vector>
class Solution {
public:
    /**
     * lfu design
     * @param operators int整型vector<vector<>> ops
     * @param k int整型 the k
     * @return int整型vector
     */
    unordered_map<int, int> key2val; //键值队
    unordered_map<int, int> key2freq;   //键及其对应的频率
    unordered_map<int, list<int>> freq2dlist; //每个频率下的所有键
    unordered_map<int, list<int>::iterator> key2iter; //每个键所在的队列位置
    int capacity;
    int m_min;

    int get(int key){
        //key未出现或已被移除，返回-1
        if(key2val.find(key)==key2val.end()) return -1;

        //获得key对应的频率
        int f = key2freq[key];
        //从对应频率的队列中删除该键
        freq2dlist[f].erase(key2iter[key]);
        if(freq2dlist[f].size()==0){
            freq2dlist.erase(f);
            if(f==m_min) ++m_min;
        }
        ++f;
        key2freq[key] = f;
        freq2dlist[f].push_back(key);
        key2iter[key] = --freq2dlist[f].end();
        return key2val[key];
    }
    void set(int key, int val){
        if(capacity==0) return;
        if(key2val.find(key)!=key2val.end()){
            key2val[key] = val;
            get(key);
        }else{
            if(key2val.size()==capacity){
                //删除频率最小且调用最早
                //这里是容器，不是迭代器，所以要用引用
                auto& d = freq2dlist[m_min];
                auto k = d.front();
                d.pop_front();
                if(d.size()==0) freq2dlist.erase(m_min);
                key2iter.erase(k);
                key2freq.erase(k);
                key2val.erase(k);
            }

            key2val[key] = val;
            key2freq[key] = 1;
            freq2dlist[1].push_back(key);
            key2iter[key] = --freq2dlist[1].end();

            m_min = 1;
        }
    }
    vector<int> LFU(vector<vector<int> >& operators, int k) {
        // write code here
        capacity = k;
        vector<int> ans;
        for(auto& i:operators){
            if(i[0]==1){
                set(i[1], i[2]);
            }else if(i[0]==2){
                int tmp = get(i[1]);
                ans.push_back(tmp);
            }
        }

        return ans;
    }
};
```