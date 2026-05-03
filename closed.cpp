#include <iostream>
using namespace std;

#define SIZE 10
#define EMPTY -1
#define DELETED -2

// ── hash function ─────────────────────────────────────────
int hashFn(int key) {
    return key % SIZE;
}

// ============================================================
//  LINEAR PROBING
// ============================================================

void lp_init(int* table) {
    for (int i = 0; i < SIZE; i++)
        table[i] = EMPTY;
}

void lp_insert(int* table, int key) {
    int idx = hashFn(key);
    for (int i = 0; i < SIZE; i++) {
        int probe = (idx + i) % SIZE;           // step = +1
        if (table[probe] == EMPTY || table[probe] == DELETED) {
            table[probe] = key;
            cout << "[LP] Inserted " << key << " at slot " << probe << "\n";
            return;
        }
        if (table[probe] == key) {
            cout << "[LP] Key " << key << " already exists at slot " << probe << "\n";
            return;
        }
    }
    cout << "[LP] Table full! Cannot insert " << key << "\n";
}

int lp_search(int* table, int key) {
    int idx = hashFn(key);
    for (int i = 0; i < SIZE; i++) {
        int probe = (idx + i) % SIZE;
        if (table[probe] == EMPTY)  return -1;     // definitely not here
        if (table[probe] == key)    return probe;  // found
    }
    return -1;
}

void lp_delete(int* table, int key) {
    int slot = lp_search(table, key);
    if (slot == -1) {
        cout << "[LP] Key " << key << " not found\n";
        return;
    }
    table[slot] = DELETED;   // tombstone — keeps probe chains intact
    cout << "[LP] Deleted " << key << " from slot " << slot << "\n";
}

void lp_display(int* table) {
    cout << "\n--- Linear Probing Table ---\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "Slot[" << i << "]: ";
        if      (table[i] == EMPTY)   cout << "EMPTY";
        else if (table[i] == DELETED) cout << "DELETED";
        else                          cout << table[i];
        cout << "\n";
    }
}

// ============================================================
//  QUADRATIC PROBING
// ============================================================

void qp_init(int* table) {
    for (int i = 0; i < SIZE; i++)
        table[i] = EMPTY;
}

void qp_insert(int* table, int key) {
    int idx = hashFn(key);
    for (int i = 0; i < SIZE; i++) {
        int probe = (idx + i * i) % SIZE;        // step = i²
        if (table[probe] == EMPTY || table[probe] == DELETED) {
            table[probe] = key;
            cout << "[QP] Inserted " << key << " at slot " << probe << "\n";
            return;
        }
        if (table[probe] == key) {
            cout << "[QP] Key " << key << " already exists at slot " << probe << "\n";
            return;
        }
    }
    cout << "[QP] No slot found for " << key << " (table full or bad size)\n";
}

int qp_search(int* table, int key) {
    int idx = hashFn(key);
    for (int i = 0; i < SIZE; i++) {
        int probe = (idx + i * i) % SIZE;
        if (table[probe] == EMPTY)  return -1;
        if (table[probe] == key)    return probe;
    }
    return -1;
}

void qp_delete(int* table, int key) {
    int slot = qp_search(table, key);
    if (slot == -1) {
        cout << "[QP] Key " << key << " not found\n";
        return;
    }
    table[slot] = DELETED;
    cout << "[QP] Deleted " << key << " from slot " << slot << "\n";
}

void qp_display(int* table) {
    cout << "\n--- Quadratic Probing Table ---\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "Slot[" << i << "]: ";
        if      (table[i] == EMPTY)   cout << "EMPTY";
        else if (table[i] == DELETED) cout << "DELETED";
        else                          cout << table[i];
        cout << "\n";
    }
}

// ============================================================
//  MAIN
// ============================================================

int main() {
    // ── Linear Probing demo ───────────────────────────────
    cout << "========================================\n";
    cout << "  CLOSED HASHING — LINEAR PROBING\n";
    cout << "========================================\n";

    int lp_table[SIZE];

    lp_init(lp_table);

    lp_insert(lp_table, 10);
    lp_insert(lp_table, 20);   // collision with 10 → probes slot 1
    lp_insert(lp_table, 30);   // collision → probes slot 2
    lp_insert(lp_table, 15);
    lp_insert(lp_table, 7);
    lp_insert(lp_table, 17);   // collision with 7 → probes next free
    lp_display(lp_table);

    cout << "\nSearch(20): slot " << lp_search(lp_table, 20) << "\n";
    cout << "Search(99): slot " << lp_search(lp_table, 99) << " (not found = -1)\n";

    lp_delete(lp_table, 20);
    lp_display(lp_table);

    // ── Quadratic Probing demo ────────────────────────────
    cout << "\n========================================\n";
    cout << "  CLOSED HASHING — QUADRATIC PROBING\n";
    cout << "========================================\n";

    int qp_table[SIZE];
    qp_init(qp_table);

    qp_insert(qp_table, 10);
    qp_insert(qp_table, 20);   // collision with 10 → probe at 1² = slot 1
    qp_insert(qp_table, 30);   // collision → probe at 2² = slot 4
    qp_insert(qp_table, 15);
    qp_insert(qp_table, 7);
    qp_insert(qp_table, 17);
    qp_display(qp_table);

    cout << "\nSearch(30): slot " << qp_search(qp_table, 30) << "\n";
    cout << "Search(99): slot " << qp_search(qp_table, 99) << " (not found = -1)\n";

    qp_delete(qp_table, 30);
    qp_display(qp_table);

    return 0;
}