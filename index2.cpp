
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ============================================================
//  SECTION 1 — HASH FUNCTIONS
// ============================================================

// 1a. Integer hash (modulo)
int hashInt(int key, int tableSize) {
    return abs(key) % tableSize;
}

// 1b. String hash (djb2 — classic & fast)
int hashString(const string& key, int tableSize) {
    unsigned long hash = 5381;
    for (char c : key)
        hash = ((hash << 5) + hash) + c;   // hash * 33 + c
    return hash % tableSize;
}

// 1c. Polynomial rolling hash (better distribution for strings)
int hashPolynomial(const string& key, int tableSize) {
    long long hash = 0;
    long long p = 31, pPow = 1;
    for (char c : key) {
        hash = (hash + (c - 'a' + 1) * pPow) % tableSize;
        pPow = (pPow * p) % tableSize;
    }
    return (int)hash;
}

// ============================================================
//  SECTION 2 — SEPARATE CHAINING (linked-list buckets)
// ============================================================

struct ChainNode {
    int   key;
    int   value;
    ChainNode* next;   // <-- pointer to next node in chain

    ChainNode(int k, int v) : key(k), value(v), next(nullptr) {}
};

class ChainingHashTable {
private:
    ChainNode** table;   // array of pointers to chain heads
    int size;
    int count;

public:
    ChainingHashTable(int sz) : size(sz), count(0) {
        table = new ChainNode*[size];   // allocate pointer array
        for (int i = 0; i < size; i++)
            table[i] = nullptr;
    }

    ~ChainingHashTable() {
        for (int i = 0; i < size; i++) {
            ChainNode* cur = table[i];
            while (cur) {                 // free every node in chain
                ChainNode* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] table;
    }

    void insert(int key, int value) {
        int idx = hashInt(key, size);
        ChainNode* cur = table[idx];

        // Update if key already exists
        while (cur) {
            if (cur->key == key) { cur->value = value; return; }
            cur = cur->next;
        }

        // Prepend new node (O(1))
        ChainNode* node = new ChainNode(key, value);
        node->next = table[idx];
        table[idx] = node;
        count++;
    }

    int* search(int key) {
        int idx = hashInt(key, size);
        ChainNode* cur = table[idx];
        while (cur) {
            if (cur->key == key) return &cur->value;
            cur = cur->next;
        }
        return nullptr;   // not found
    }

    bool remove(int key) {
        int idx = hashInt(key, size);
        ChainNode* cur  = table[idx];
        ChainNode* prev = nullptr;
        while (cur) {
            if (cur->key == key) {
                if (prev) prev->next = cur->next;
                else       table[idx] = cur->next;
                delete cur;
                count--;
                return true;
            }
            prev = cur;
            cur  = cur->next;
        }
        return false;
    }

    void display() const {
        cout << "\n--- Chaining Hash Table ---\n";
        for (int i = 0; i < size; i++) {
            cout << "Bucket[" << i << "]: ";
            ChainNode* cur = table[i];
            while (cur) {
                cout << "(" << cur->key << "," << cur->value << ")";
                if (cur->next) cout << " -> ";
                cur = cur->next;
            }
            cout << (table[i] ? " -> null" : "null") << "\n";
        }
    }

    double loadFactor() const { return (double)count / size; }
};

// ============================================================
//  SECTION 3 — OPEN ADDRESSING : LINEAR PROBING
// ============================================================

struct OAEntry {
    int  key;
    int  value;
    bool occupied;
    bool deleted;   // tombstone for lazy deletion

    OAEntry() : key(-1), value(-1), occupied(false), deleted(false) {}
};

class LinearProbingTable {
private:
    OAEntry* table;   // pointer to flat array
    int size;
    int count;

    int hash(int key) const { return abs(key) % size; }

public:
    LinearProbingTable(int sz) : size(sz), count(0) {
        table = new OAEntry[size];   // single contiguous allocation
    }
    ~LinearProbingTable() { delete[] table; }

    void insert(int key, int value) {
        if (loadFactor() >= 0.7) {
            cout << "[Linear] Load factor high — consider rehashing!\n";
        }
        int idx = hash(key);
        for (int i = 0; i < size; i++) {
            int probe = (idx + i) % size;   // linear step: +1 each time
            if (!table[probe].occupied || table[probe].deleted) {
                table[probe] = {key, value, true, false};
                count++;
                return;
            }
            if (table[probe].key == key) {   // update existing
                table[probe].value = value;
                return;
            }
        }
        cout << "[Linear] Table full!\n";
    }

    int* search(int key) {
        int idx = hash(key);
        for (int i = 0; i < size; i++) {
            int probe = (idx + i) % size;
            if (!table[probe].occupied && !table[probe].deleted) break;
            if (table[probe].occupied && table[probe].key == key)
                return &table[probe].value;
        }
        return nullptr;
    }

    bool remove(int key) {
        int idx = hash(key);
        for (int i = 0; i < size; i++) {
            int probe = (idx + i) % size;
            if (!table[probe].occupied && !table[probe].deleted) break;
            if (table[probe].occupied && table[probe].key == key) {
                table[probe].occupied = false;
                table[probe].deleted  = true;   // tombstone
                count--;
                return true;
            }
        }
        return false;
    }

    void display() const {
        cout << "\n--- Linear Probing Table ---\n";
        for (int i = 0; i < size; i++) {
            cout << "Slot[" << i << "]: ";
            if      (table[i].occupied) cout << "(" << table[i].key << "," << table[i].value << ")";
            else if (table[i].deleted)  cout << "[DELETED]";
            else                        cout << "empty";
            cout << "\n";
        }
    }

    double loadFactor() const { return (double)count / size; }
};

// ============================================================
//  SECTION 4 — OPEN ADDRESSING : QUADRATIC PROBING
// ============================================================

class QuadraticProbingTable {
private:
    OAEntry* table;
    int size;
    int count;

    int hash(int key) const { return abs(key) % size; }

public:
    QuadraticProbingTable(int sz) : size(sz), count(0) {
        table = new OAEntry[size];
    }
    ~QuadraticProbingTable() { delete[] table; }

    void insert(int key, int value) {
        int idx = hash(key);
        for (int i = 0; i < size; i++) {
            int probe = (idx + i*i) % size;   // quadratic step: i²
            if (!table[probe].occupied || table[probe].deleted) {
                table[probe] = {key, value, true, false};
                count++;
                return;
            }
            if (table[probe].key == key) {
                table[probe].value = value;
                return;
            }
        }
        cout << "[Quadratic] No slot found — table too full or bad size!\n";
    }

    int* search(int key) {
        int idx = hash(key);
        for (int i = 0; i < size; i++) {
            int probe = (idx + i*i) % size;
            if (!table[probe].occupied && !table[probe].deleted) break;
            if (table[probe].occupied && table[probe].key == key)
                return &table[probe].value;
        }
        return nullptr;
    }

    void display() const {
        cout << "\n--- Quadratic Probing Table ---\n";
        for (int i = 0; i < size; i++) {
            cout << "Slot[" << i << "]: ";
            if      (table[i].occupied) cout << "(" << table[i].key << "," << table[i].value << ")";
            else if (table[i].deleted)  cout << "[DELETED]";
            else                        cout << "empty";
            cout << "\n";
        }
    }

    double loadFactor() const { return (double)count / size; }
};

// ============================================================
//  SECTION 5 — OPEN ADDRESSING : DOUBLE HASHING
// ============================================================

class DoubleHashingTable {
private:
    OAEntry* table;
    int size;
    int count;

    int hash1(int key) const { return abs(key) % size; }
    // hash2 must never return 0, and should be coprime with size
    int hash2(int key) const { return 7 - (abs(key) % 7); }

public:
    DoubleHashingTable(int sz) : size(sz), count(0) {
        table = new OAEntry[size];
    }
    ~DoubleHashingTable() { delete[] table; }

    void insert(int key, int value) {
        int h1 = hash1(key);
        int h2 = hash2(key);
        for (int i = 0; i < size; i++) {
            int probe = (h1 + i * h2) % size;   // double-hash step
            if (!table[probe].occupied || table[probe].deleted) {
                table[probe] = {key, value, true, false};
                count++;
                return;
            }
            if (table[probe].key == key) {
                table[probe].value = value;
                return;
            }
        }
        cout << "[DoubleHash] Table full!\n";
    }

    int* search(int key) {
        int h1 = hash1(key);
        int h2 = hash2(key);
        for (int i = 0; i < size; i++) {
            int probe = (h1 + i * h2) % size;
            if (!table[probe].occupied && !table[probe].deleted) break;
            if (table[probe].occupied && table[probe].key == key)
                return &table[probe].value;
        }
        return nullptr;
    }

    void display() const {
        cout << "\n--- Double Hashing Table ---\n";
        for (int i = 0; i < size; i++) {
            cout << "Slot[" << i << "]: ";
            if      (table[i].occupied) cout << "(" << table[i].key << "," << table[i].value << ")";
            else if (table[i].deleted)  cout << "[DELETED]";
            else                        cout << "empty";
            cout << "\n";
        }
    }

    double loadFactor() const { return (double)count / size; }
};

// ============================================================
//  SECTION 6 — DYNAMIC REHASHING (chaining-based)
// ============================================================

class RehashingHashTable {
private:
    ChainNode** table;
    int size;
    int count;

    int hash(int key) const { return abs(key) % size; }

    void insertInternal(ChainNode** tbl, int sz, int key, int value) {
        int idx = abs(key) % sz;
        ChainNode* node = new ChainNode(key, value);
        node->next = tbl[idx];
        tbl[idx]   = node;
    }

    void rehash() {
        int oldSize    = size;
        ChainNode** old = table;
        size  = size * 2 + 1;   // new prime-ish size
        table = new ChainNode*[size];
        for (int i = 0; i < size; i++) table[i] = nullptr;
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            ChainNode* cur = old[i];
            while (cur) {
                insertInternal(table, size, cur->key, cur->value);
                count++;
                ChainNode* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] old;
        cout << "[Rehash] Resized to " << size << "\n";
    }

public:
    RehashingHashTable(int sz = 7) : size(sz), count(0) {
        table = new ChainNode*[size];
        for (int i = 0; i < size; i++) table[i] = nullptr;
    }

    ~RehashingHashTable() {
        for (int i = 0; i < size; i++) {
            ChainNode* cur = table[i];
            while (cur) {
                ChainNode* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] table;
    }

    void insert(int key, int value) {
        if ((double)count / size >= 0.75) rehash();
        int idx = hash(key);
        ChainNode* cur = table[idx];
        while (cur) {
            if (cur->key == key) { cur->value = value; return; }
            cur = cur->next;
        }
        ChainNode* node = new ChainNode(key, value);
        node->next = table[idx];
        table[idx] = node;
        count++;
    }

    void display() const {
        cout << "\n--- Rehashing Table (size=" << size
             << ", load=" << (double)count/size << ") ---\n";
        for (int i = 0; i < size; i++) {
            cout << "Bucket[" << i << "]: ";
            ChainNode* cur = table[i];
            while (cur) {
                cout << "(" << cur->key << "," << cur->value << ")";
                if (cur->next) cout << " -> ";
                cur = cur->next;
            }
            cout << "\n";
        }
    }
};

// ============================================================
//  SECTION 7 — GENERIC TEMPLATE HASHMAP (string → int)
// ============================================================

template<typename K, typename V>
struct KVNode {
    K key;
    V value;
    KVNode<K,V>* next;   // pointer to next node in chain
    KVNode(K k, V v) : key(k), value(v), next(nullptr) {}
};

template<typename K, typename V>
class HashMap {
private:
    KVNode<K,V>** buckets;   // pointer-to-pointer-to-node
    int capacity;
    int count;

    int hash(const string& k) const {
        unsigned long h = 5381;
        for (char c : k) h = ((h << 5) + h) + c;
        return h % capacity;
    }
    int hash(int k) const { return abs(k) % capacity; }

public:
    HashMap(int cap = 11) : capacity(cap), count(0) {
        buckets = new KVNode<K,V>*[capacity];
        for (int i = 0; i < capacity; i++) buckets[i] = nullptr;
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            KVNode<K,V>* cur = buckets[i];
            while (cur) {
                KVNode<K,V>* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
        delete[] buckets;
    }

    void put(K key, V value) {
        int idx = hash(key);
        KVNode<K,V>* cur = buckets[idx];
        while (cur) {
            if (cur->key == key) { cur->value = value; return; }
            cur = cur->next;
        }
        auto* node = new KVNode<K,V>(key, value);
        node->next = buckets[idx];
        buckets[idx] = node;
        count++;
    }

    V* get(K key) {
        int idx = hash(key);
        KVNode<K,V>* cur = buckets[idx];
        while (cur) {
            if (cur->key == key) return &cur->value;
            cur = cur->next;
        }
        return nullptr;   // null pointer = key absent
    }

    bool erase(K key) {
        int idx = hash(key);
        KVNode<K,V>* cur  = buckets[idx];
        KVNode<K,V>* prev = nullptr;
        while (cur) {
            if (cur->key == key) {
                if (prev) prev->next = cur->next;
                else       buckets[idx] = cur->next;
                delete cur;
                count--;
                return true;
            }
            prev = cur;
            cur  = cur->next;
        }
        return false;
    }

    void display() const {
        cout << "\n--- Generic HashMap ---\n";
        for (int i = 0; i < capacity; i++) {
            KVNode<K,V>* cur = buckets[i];
            if (!cur) continue;
            cout << "Bucket[" << i << "]: ";
            while (cur) {
                cout << "[" << cur->key << " => " << cur->value << "]";
                if (cur->next) cout << " -> ";
                cur = cur->next;
            }
            cout << "\n";
        }
    }

    int size() const { return count; }
};

// ============================================================
//  MAIN — DEMO ALL CASES
// ============================================================

int main() {
    cout << "========================================\n";
    cout << "  HASHING IN C++ — ALL CASES DEMO\n";
    cout << "========================================\n";

    // --- Hash Functions ---
    cout << "\n[Hash Functions]\n";
    cout << "hashInt(42, 10)       = " << hashInt(42, 10) << "\n";
    cout << "hashString(\"hello\",10)= " << hashString("hello", 10) << "\n";
    cout << "hashPolynomial(\"abc\") = " << hashPolynomial("abc", 10) << "\n";

    // --- Separate Chaining ---
    {
        ChainingHashTable ct(5);
        ct.insert(10, 100);
        ct.insert(15, 150);   // collision with 10 (both % 5 == 0)
        ct.insert(20, 200);   // another collision
        ct.insert(7,  70);
        ct.insert(3,  30);
        ct.display();

        int* v = ct.search(15);
        cout << "Search(15): " << (v ? to_string(*v) : "not found") << "\n";
        ct.remove(15);
        cout << "After remove(15):\n";
        ct.display();
    }

    // --- Linear Probing ---
    {
        LinearProbingTable lt(7);
        lt.insert(10, 100);
        lt.insert(17, 170);   // same hash as 10
        lt.insert(24, 240);   // same hash again — probes forward
        lt.insert(3,  30);
        lt.display();

        int* v = lt.search(17);
        cout << "Search(17): " << (v ? to_string(*v) : "not found") << "\n";
        lt.remove(17);
        cout << "After remove(17) [tombstone]:\n";
        lt.display();
    }

    // --- Quadratic Probing ---
    {
        QuadraticProbingTable qt(11);
        qt.insert(20, 200);
        qt.insert(31, 310);   // same hash as 20 — probes at 1², 2², ...
        qt.insert(42, 420);
        qt.insert(5,  50);
        qt.display();
    }

    // --- Double Hashing ---
    {
        DoubleHashingTable dt(11);
        dt.insert(20, 200);
        dt.insert(31, 310);
        dt.insert(42, 420);
        dt.insert(53, 530);
        dt.display();

        int* v = dt.search(42);
        cout << "Search(42): " << (v ? to_string(*v) : "not found") << "\n";
    }

    // --- Dynamic Rehashing ---
    {
        RehashingHashTable rht(3);   // tiny initial size to trigger rehash
        for (int i = 0; i < 10; i++)
            rht.insert(i * 7, i * 100);   // forces a rehash
        rht.display();
    }

    // --- Generic Template HashMap (string -> int) ---
    {
        HashMap<string, int> hm;
        hm.put("apple",  5);
        hm.put("banana", 3);
        hm.put("cherry", 9);
        hm.put("apple",  7);   // update existing key
        hm.display();

        int* v = hm.get("banana");
        cout << "get(\"banana\"): " << (v ? to_string(*v) : "not found") << "\n";
        hm.erase("banana");
        cout << "After erase(\"banana\"):\n";
        hm.display();
    }

    cout << "\n========== ALL CASES COMPLETE ==========\n";
    return 0;
}