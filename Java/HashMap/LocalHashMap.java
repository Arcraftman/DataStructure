/* 继承的 AbstractMap
AbstractMap 是一个抽象类，它实现了 Map 接口的大部分方法。
HashMap 继承了 AbstractMap，因此它只需要覆盖一些关键方法（例如 get() 和 put()）即可。

为什么继承 AbstractMap？
提供通用的 Map 功能，比如 entrySet()、equals() 和 hashCode()。
减少重复代码的编写，方便扩展。

实现的 Map<K, V>
Map 是一个接口，定义了键值对数据结构的基本行为，包括：
put(K key, V value)：添加键值对。
get(Object key)：根据键获取值。
remove(Object key)：删除键值对。
containsKey(Object key) 和 containsValue(Object value)：判断键或值是否存在。
size()：返回键值对的数量。
HashMap 作为 Map 的实现类，必须提供这些方法的具体实现。

实现的 Cloneable
Cloneable 是一个标记接口，用于表示该类可以被克隆（通过 clone() 方法）。
HashMap 提供了一个 clone() 方法，用于创建当前 HashMap 的浅拷贝。

为什么实现 Cloneable？
允许用户快速复制一个 HashMap，而不需要逐个拷贝键值对。

实现的 Serializable
Serializable 是一个标记接口，用于表示该类可以被序列化。
HashMap 实现了 Serializable，因此可以通过对象流（如 ObjectOutputStream 和 ObjectInputStream）进行读写。

为什么实现 Serializable？
使 HashMap 能够持久化到磁盘，或者通过网络传输 */

import java.io.Serializable;
import java.util.AbstractMap;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

public class LocalHashMap<K,V> extends AbstractMap<K,V> implements Map<K,V> ,Cloneable ,Serializable {
    
    static final int DEFAULT_INITIAL_CAPACITY = 1 << 4;
    
    static final int MAXIMUM_CAPACITY = 1 << 30;

    static final float DEFAULT_LOAD_FACTOR = 0.75f;

    /*
    默认负载因子。
    作用：控制哈希表何时进行扩容。 细节： 负载因子决定了 HashMap 的容量和性能之间的平衡。
    默认值 0.75 表示，当哈希表中填充的元素数量达到容量的 75% 时，将触发一次扩容操作（即表的容量加倍）。
    这是一个折衷值，既保证了较高的空间利用率，又能提供较好的性能。
    */

    static final int TREEIFY_THRESHOLD = 8;
    
    /*
    含义：链表转化为红黑树的阈值。
    作用：当单个桶中的节点数（哈希冲突导致的链表长度）达到 8 时，HashMap 会将链表转换为红黑树，以提高查询和更新的性能。
    细节：
    红黑树的查询和更新时间复杂度为 O(log n)，而链表是 O(n)。
    设置此阈值的目的是避免哈希冲突过多时，链表查询性能的退化。
    转换条件：
    桶中的节点数 ≥ 8。
    */

    static final int UNTREEIFY_THRESHOLD = 6;

    /*
    含义：红黑树退化回链表的阈值。
    作用：当树化的桶中的节点数量减少到 6（即小于 TREEIFY_THRESHOLD），并且发生了表缩小（resize）操作时，HashMap 会将红黑树重新转化为链表。
    细节：
    该值通常小于 TREEIFY_THRESHOLD（8），以避免频繁地在树和链表之间来回转换。
    当表缩小时，树化的桶可能会变得稀疏，为了节省空间，将其重新转化为链表.
    */

    static final int MIN_TREEIFY_CAPACITY = 64;

    /*
    含义：允许树化的最小表容量。
    作用：限制何时允许链表转化为红黑树。如果当前哈希表的容量小于 64，则会优先选择扩容，而不是将链表转化为红黑树。
    细节：
    目的：在小容量表中避免树化操作，因为树化操作相对复杂，会增加额外的内存和计算成本。
    设置为 4 * TREEIFY_THRESHOLD 是为了确保哈希表的容量足够大，从而降低哈希冲突的概率，避免不必要的树化。
    */
    static class LocalNode<K,V> implements Map.Entry<K,V> {
        final int hash;
        final K key;
        V value;
        LocalNode<K,V> next;

        LocalNode(int hash , K key , V value , LocalNode<K,V> next){
            this.hash = hash;
            this.key = key;
            this.value = value;
            this.next = next;
        }

        public final K getKey() { return key ;}
        public final V getValue()      { return value; }
        public final String toString() { return key + "=" + value; }
        public V setValue(V newValue) {
            V oldValue = value;
            value = newValue;
            return oldValue;
        }

        public final boolean equals(Object o){
            if ( o == this ) return true;

            return o instanceof Map.Entry<?,?> e && Objects.equals(key,e.getKey()) && Objects.equals(value, e.getValue());
        }
        
        };


    }


}

    