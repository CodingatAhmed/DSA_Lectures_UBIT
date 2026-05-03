#include <iostream>
using namespace std;

#define BUCKETS   7      // number of hash buckets
#define POOL_SIZE 20     // max total nodes across all chains

// ── parallel arrays that together form a linked-list pool ──
int keys[POOL_SIZE];     // key stored at node i
int next_node[POOL_SIZE];// index of next node in chain (-1 = end)
bool used[POOL_SIZE];    // is node slot i occupied?

int head[BUCKETS];       // head index for each bucket (-1 = empty)

// ── hash function ─────────────────────────────────────────
int hashFn(int key) {
    return key % BUCKETS;
}

// ── allocate a free node from the pool ────────────────────
// returns index, or -1 if pool is full
int alloc_node() {
    for (int i = 0; i < POOL_SIZE; i++) {
        if (!used[i]) {
            used[i] = true;
            return i;
        }
    }
    return -1;   // pool exhausted
}

// ── free a node back to the pool ──────────────────────────
void free_node(int idx) {
    used[idx]      = false;
    keys[idx]      = -1;
    next_node[idx] = -1;
}

// ── initialise everything ─────────────────────────────────
void init() {
    for (int i = 0; i < POOL_SIZE; i++) {
        keys[i]      = -1;
        next_node[i] = -1;
        used[i]      = false;
    }
    for (int i = 0; i < BUCKETS; i++)
        head[i] = -1;
}

// ── insert ────────────────────────────────────────────────
void insert(int key) {
    int bucket = hashFn(key);
    int cur    = head[bucket];

    // check if key already exists
    while (cur != -1) {
        if (keys[cur] == key) {
            cout << "[Chain] Key " << key << " already exists in bucket " << bucket << "\n";
            return;
        }
        cur = next_node[cur];
    }

    // get a free node
    int node = alloc_node();
    if (node == -1) {
        cout << "[Chain] Node pool full! Cannot insert " << key << "\n";
        return;
    }

    keys[node]      = key;
    next_node[node] = head[bucket];   // prepend to chain
    head[bucket]    = node;

    cout << "[Chain] Inserted " << key << " into bucket " << bucket
         << " (node slot " << node << ")\n";
}

// ── search ────────────────────────────────────────────────
// returns node index if found, -1 otherwise
int search(int key) {
    int bucket = hashFn(key);
    int cur    = head[bucket];
    while (cur != -1) {
        if (keys[cur] == key) return cur;
        cur = next_node[cur];
    }
    return -1;
}

// ── delete ────────────────────────────────────────────────
void delete_key(int key) {
    int bucket = hashFn(key);
    int cur    = head[bucket];
    int prev   = -1;

    while (cur != -1) {
        if (keys[cur] == key) {
            if (prev == -1)
                head[bucket] = next_node[cur];   // remove head
            else
                next_node[prev] = next_node[cur];// bypass node

            free_node(cur);
            cout << "[Chain] Deleted " << key << " from bucket " << bucket << "\n";
            return;
        }
        prev = cur;
        cur  = next_node[cur];
    }
    cout << "[Chain] Key " << key << " not found\n";
}

// ── display ───────────────────────────────────────────────
void display() {
    cout << "\n--- Open Hashing (Separate Chaining) Table ---\n";
    for (int i = 0; i < BUCKETS; i++) {
        cout << "Bucket[" << i << "]: ";
        int cur = head[i];
        if (cur == -1) {
            cout << "null";
        } else {
            while (cur != -1) {
                cout << keys[cur];
                if (next_node[cur] != -1) cout << " -> ";
                cur = next_node[cur];
            }
            cout << " -> null";
        }
        cout << "\n";
    }
}

// ── print raw pool (for debugging pointer-index logic) ────
void display_pool() {
    cout << "\n--- Node Pool (slot | key | next) ---\n";
    for (int i = 0; i < POOL_SIZE; i++) {
        if (used[i])
            cout << "Slot[" << i << "]: key=" << keys[i]
                 << "  next=" << next_node[i] << "\n";
    }
}

// ============================================================
//  MAIN
// ============================================================

int main() {
    cout << "========================================\n";
    cout << "  OPEN HASHING — SEPARATE CHAINING\n";
    cout << "  (Linked List via Parallel Arrays)\n";
    cout << "========================================\n";

    init();

    insert(10);
    insert(17);   // 17 % 7 = 3
    insert(24);   // 24 % 7 = 3  → collision with 17, prepends
    insert(31);   // 31 % 7 = 3  → collision, prepends
    insert(5);
    insert(12);
    insert(19);   // 19 % 7 = 5
    insert(26);   // 26 % 7 = 5  → collision with 19

    display();
    display_pool();

    cout << "\nSearch(24): node slot = " << search(24) << "\n";
    cout << "Search(99): node slot = " << search(99) << " (not found = -1)\n";

    cout << "\n";
    delete_key(24);   // middle of chain
    delete_key(10);   // head of its chain
    delete_key(99);   // not present

    display();

    return 0;
}