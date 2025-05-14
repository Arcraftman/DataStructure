package edu.suibe.dev;
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

import java.util.AbstractMap;
import java.util.AbstractSet;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Objects;
import java.util.Set;

import org.w3c.dom.Node;

public class LocalHashMap<K, V> extends AbstractMap<K, V> implements Map<K, V> {

    static final int DEFAULT_INITIAL_CAPACITY = 1 << 4;

    static final int MAXIMUM_CAPACITY = 1 << 30;

    static final float DEFAULT_LOAD_FACTOR = 0.75f;

    /*
     * 默认负载因子。
     * 作用：控制哈希表何时进行扩容。 细节： 负载因子决定了 HashMap 的容量和性能之间的平衡。
     * 默认值 0.75 表示，当哈希表中填充的元素数量达到容量的 75% 时，将触发一次扩容操作（即表的容量加倍）。
     * 这是一个折衷值，既保证了较高的空间利用率，又能提供较好的性能。
     */

    static final int TREEIFY_THRESHOLD = 8;

    /*
     * 含义：链表转化为红黑树的阈值。
     * 作用：当单个桶中的节点数（哈希冲突导致的链表长度）达到 8 时，HashMap 会将链表转换为红黑树，以提高查询和更新的性能。
     * 细节：
     * 红黑树的查询和更新时间复杂度为 O(log n)，而链表是 O(n)。
     * 设置此阈值的目的是避免哈希冲突过多时，链表查询性能的退化。
     * 转换条件：
     * 桶中的节点数 ≥ 8。
     */

    static final int UNTREEIFY_THRESHOLD = 6;

    /*
     * 含义：红黑树退化回链表的阈值。
     * 作用：当树化的桶中的节点数量减少到 6（即小于 TREEIFY_THRESHOLD），并且发生了表缩小（resize）操作时，HashMap
     * 会将红黑树重新转化为链表。
     * 细节：
     * 该值通常小于 TREEIFY_THRESHOLD（8），以避免频繁地在树和链表之间来回转换。
     * 当表缩小时，树化的桶可能会变得稀疏，为了节省空间，将其重新转化为链表.
     */

    static final int MIN_TREEIFY_CAPACITY = 64;

    /*
     * 含义：允许树化的最小表容量。
     * 作用：限制何时允许链表转化为红黑树。如果当前哈希表的容量小于 64，则会优先选择扩容，而不是将链表转化为红黑树。
     * 细节：
     * 目的：在小容量表中避免树化操作，因为树化操作相对复杂，会增加额外的内存和计算成本。
     * 设置为 4 * TREEIFY_THRESHOLD 是为了确保哈希表的容量足够大，从而降低哈希冲突的概率，避免不必要的树化。
     */

    float loadFactor;

    int threshold;

    transient Set<Map.Entry<K, V>> entrySet;

    transient int size;

    transient LocalNode<K, V>[] table;

    public LocalHashMap() {
        this.loadFactor = DEFAULT_LOAD_FACTOR;
    }

    public LocalHashMap(int initialCapacity) {
        this(initialCapacity, DEFAULT_LOAD_FACTOR);
    }

    public LocalHashMap(int initialCapacity, float loadFactor) {
        if (initialCapacity < 0)
            throw new IllegalArgumentException("Illegal initial capacity: " +
                    initialCapacity);
        if (initialCapacity > MAXIMUM_CAPACITY)
            initialCapacity = MAXIMUM_CAPACITY;
        if (loadFactor <= 0 || Float.isNaN(loadFactor))
            throw new IllegalArgumentException("Illegal load factor: " + loadFactor);
        this.loadFactor = loadFactor;
        this.threshold = tableSizeFor(initialCapacity);
    }

    static final int tableSizeFor(int cap) {
        int n = -1 >>> Integer.numberOfLeadingZeros(cap - 1);
        return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
    }

    static class LocalNode<K, V> implements Map.Entry<K, V> {
        final int hash;
        final K key;
        V value;
        LocalNode<K, V> next;

        LocalNode(int hash, K key, V value, LocalNode<K, V> next) {
            this.hash = hash;
            this.key = key;
            this.value = value;
            this.next = next;
        }

        public final K getKey() {
            return key;
        }

        public final V getValue() {
            return value;
        }

        public final String toString() {
            return key + "=" + value;
        }

        public V setValue(V newValue) {
            V oldValue = value;
            value = newValue;
            return oldValue;
        }

        public final boolean equals(Object o) {
            if (o == this)
                return true;

            return o instanceof Map.Entry<?, ?> e && Objects.equals(key, e.getKey())
                    && Objects.equals(value, e.getValue());
        }

    }

    final LocalNode<K, V> getNode(int hash, Object key) {
        LocalNode<K, V>[] tab = table;
        LocalNode<K, V> first = tab[(tab.length - 1) & hash];
        LocalNode<K, V> e = first;

        while (e != null) {
            if (e.hash == hash &&
                    ((key == e.key) || (key != null && key.equals(e.key))))
                return e;
            e = e.next;
        }
        return null;
    }

    // EntrySet implementation
    final class EntrySet extends AbstractSet<Map.Entry<K, V>> {
        public EntrySet() {
        };

        public final int size() {
            return size;
        }

        public final void clear() {
            LocalHashMap.this.clear();
        }

        public final Iterator<Map.Entry<K, V>> iterator() {
            return new EntryIterator();
        }

        public final boolean contains(Object o) {
            if (!(o instanceof Map.Entry))
                return false;
            Map.Entry<?, ?> e = (Map.Entry<?, ?>) o;
            Object key = e.getKey();
            LocalNode<K, V> candidate = getNode(hash(key), key);
            return candidate != null && candidate.equals(e);
        }

        public final boolean remove(Object o) {
            if (o instanceof Map.Entry) {
                Map.Entry<?, ?> e = (Map.Entry<?, ?>) o;
                Object key = e.getKey();
                Object value = e.getValue();
                return removeNode(hash(key), key, value, true, true) != null;
            }
            return false;
        }
    }

    public Set<Entry<K, V>> entrySet() {
        Set<Map.Entry<K, V>> es;
        return (es = entrySet) == null ? (entrySet = new EntrySet()) : es;
    };

    final class EntryIterator extends HashIterator
            implements Iterator<Map.Entry<K, V>> {
        public final Map.Entry<K, V> next() {
            return nextNode();
        }
    }

    abstract class HashIterator {
        LocalNode<K, V> next; // next entry to return
        LocalNode<K, V> current; // current entry
        int index; // current slot

        HashIterator() {
            current = next = null;
            index = 0;
            if (size > 0) { // advance to first entry
                LocalNode<K, V>[] t = table;
                while (index < t.length && (next = t[index++]) == null)
                    ;
            }
        }

        public final boolean hasNext() {
            return next != null;
        }

        final LocalNode<K, V> nextNode() {
            LocalNode<K, V>[] t;
            LocalNode<K, V> e = next;
            if (e == null)
                throw new NoSuchElementException();

            if ((next = (current = e).next) == null && (t = table) != null) {
                while (index < t.length && (next = t[index++]) == null)
                    ;
            }
            return e;
        }

        public final void remove() {
            LocalNode<K, V> p = current;
            if (p == null)
                throw new IllegalStateException();
            current = null;
            removeNode(p.hash, p.key, null, false, false);
        }
    }

    final LocalNode<K, V> removeNode(int hash, Object key, Object value,
            boolean matchValue, boolean movable) {
        LocalNode<K, V>[] tab = table;
        int index = (tab.length - 1) & hash;
        LocalNode<K, V> first = tab[index];
        LocalNode<K, V> node = null, prev = null;

        // Find the node to remove
        for (LocalNode<K, V> e = first; e != null; e = e.next) {
            if (e.hash == hash &&
                    ((key == e.key) || (key != null && key.equals(e.key)))) {
                node = e;
                break;
            }
            prev = e;
        }

        // Remove the node if found
        if (node != null && (!matchValue || (value == node.value) ||
                (value != null && value.equals(node.value)))) {
            if (prev == null) {
                tab[index] = node.next;
            } else {
                prev.next = node.next;
            }
            size--;
            return node;
        }
        return null;
    }

    static final int hash(Object key) {
        int h;
        return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
    }

    final LocalNode<K,V>[] resize() {
        LocalNode<K,V>[] oldTab = table;
        int oldCap = (oldTab == null) ? 0 : oldTab.length;
        int oldThr = threshold;
        int newCap, newThr = 0;
        if (oldCap > 0) {
            if (oldCap >= MAXIMUM_CAPACITY) {
                threshold = Integer.MAX_VALUE;
                return oldTab;
            }
            else if ((newCap = oldCap << 1) < MAXIMUM_CAPACITY &&
                     oldCap >= DEFAULT_INITIAL_CAPACITY)
                newThr = oldThr << 1; // double threshold
        }
        else if (oldThr > 0) // initial capacity was placed in threshold
            newCap = oldThr;
        else {               // zero initial threshold signifies using defaults
            newCap = DEFAULT_INITIAL_CAPACITY;
            newThr = (int)(DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
        }
        if (newThr == 0) {
            float ft = (float)newCap * loadFactor;
            newThr = (newCap < MAXIMUM_CAPACITY && ft < (float)MAXIMUM_CAPACITY ?
                      (int)ft : Integer.MAX_VALUE);
        }
        threshold = newThr;
    }

    public V put(K key, V value) {
        return putVal(hash(key), key, value, false, true);
    }

    final V putVal(int hash ,K key, V value,boolean onlyIfAbsent , boolean evict){
        LocalNode<K,V>[] t ; LocalNode<K,V> p ; int n , i;
       if ((t = table) == null || (n = t.length) == 0) {
            n = (t = resize()).length;
       }
    }

}
