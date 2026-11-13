#include <iostream>
using namespace std;

const int a = 10005;
const int b = 10005;

int c(const char d[]) {
    int e = 0;
    while (d[e] != '\0') e++;
    return e;
}

void f(const char g[], int h[], int& i) {
    int j = c(g);
    i = 0;
    if (j == 0) return;

    h[0] = 0;
    int k = 0;

    for (int l = 1; l < j; l++) {
        while (k > 0) {
            i++;
            if (g[l] == g[k]) break;
            k = h[k - 1];
        }

        if (k == 0) {
            i++;
            if (g[l] == g[k]) k++;
        }
        else {
            i++;
            if (g[l] == g[k]) k++;
        }

        h[l] = k;
    }
}

int m(const char n[], const char g[], const int h[],
    long long& i, int& o) {
    i = 0;
    o = 0;
    int p = c(n);
    int j = c(g);
    if (j == 0) return 0;
    if (j > p) return -1;

    int k = 0;
    for (int l = 0; l < p; l++) {
        while (k > 0) {
            i++;
            if (n[l] == g[k]) break;
            k = h[k - 1];
            o++;
        }

        i++;
        if (n[l] == g[k]) k++;

        if (k == j) return l - j + 1;
    }
    return -1;
}

int q(const char n[], const char g[], const int h[],
    int r[], long long& i, int& o) {
    i = 0;
    o = 0;
    int p = c(n);
    int j = c(g);
    if (j == 0) {
        r[0] = 0;
        return 1;
    }
    if (j > p) return 0;

    int k = 0;
    int s = 0;
    for (int l = 0; l < p; l++) {
        while (k > 0) {
            i++;
            if (n[l] == g[k]) break;
            k = h[k - 1];
            o++;
        }

        i++;
        if (n[l] == g[k]) k++;

        if (k == j) {
            r[s++] = l - j + 1;
            k = h[k - 1];
            o++;
        }
    }
    return s;
}

int t(const char n[], const char g[], int r[],
    long long& i) {
    i = 0;
    int p = c(n);
    int j = c(g);
    if (j == 0) {
        r[0] = 0;
        return 1;
    }
    if (j > p) return 0;

    int s = 0;
    for (int l = 0; l <= p - j; l++) {
        int k = 0;
        while (k < j) {
            i++;
            if (n[l + k] != g[k]) break;
            k++;
        }
        if (k == j) r[s++] = l;
    }
    return s;
}

bool u(const int v[], const int w[], int p) {
    for (int l = 0; l < p; l++)
        if (v[l] != w[l]) return false;
    return true;
}

void x(const int v[], int p) {
    for (int l = 0; l < p; l++)
        cout << v[l] << (l + 1 < p ? ", " : "");
    cout << "\n";
}

void y(const char n[], const char g[], const int h[]) {
    int p = c(n);
    int j = c(g);
    int k = 0;
    cout << "\nKMP TRACE\n";
    cout << "i | j | text[i] | pattern[j] | result | new j\n";

    for (int l = 0; l < p; l++) {
        while (k > 0 && n[l] != g[k]) {
            int z = k;
            k = h[k - 1];
            cout << l << " | " << z << " | " << n[l]
                << " | " << g[z] << " | mismatch, prefix fallback | "
                << k << "\n";
        }

        char aa = g[k];
        if (n[l] == g[k]) {
            k++;
            cout << l << " | " << k - 1 << " | " << n[l]
                << " | " << aa << " | match | " << k << "\n";
        }
        else {
            cout << l << " | " << k << " | " << n[l]
                << " | " << aa << " | mismatch | " << k << "\n";
        }

        if (k == j) {
            cout << "Found at position " << l - j + 1 << "\n";
            k = h[k - 1];
            cout << "After full match, prefix fallback: j = " << k << "\n";
        }
    }
}

int main() {
    cout << "PRACTICAL WORK 9 - KNUTH-MORRIS-PRATT\n\n";

    const char* ab[6] = {
        "a", "aaaa", "abcd", "ababaca", "aabaaab", "abcababcab"
    };
    int ac[6][10] = {
        { 0 },
        { 0, 1, 2, 3 },
        { 0, 0, 0, 0 },
        { 0, 0, 1, 2, 3, 0, 1 },
        { 0, 1, 0, 1, 2, 2, 3 },
        { 0, 0, 0, 1, 2, 1, 2, 3, 4, 5 }
    };
    int ad[6] = { 1, 4, 4, 7, 7, 10 };
    int h[a];
    int ae;
    int af = 0;

    cout << "PREFIX FUNCTION TESTS\n";
    for (int ag = 0; ag < 6; ag++) {
        f(ab[ag], h, ae);
        bool ah = u(h, ac[ag], ad[ag]);
        cout << "Pattern: " << ab[ag] << " | actual: ";
        x(h, ad[ag]);
        cout << (ah ? "PASS" : "FAIL") << "\n";
        if (!ah) {
            for (int l = 0; l < ad[ag]; l++) {
                if (h[l] != ac[ag][l]) {
                    cout << "First difference: index " << l
                        << ", symbol " << ab[ag][l]
                        << ", expected " << ac[ag][l]
                        << ", actual " << h[l] << "\n";
                    break;
                }
            }
        }
        else af++;
    }
    cout << "Prefix tests passed: " << af << "/6\n";

    const char* ai[10] = {
        "mississippi", "aaaa", "abababa", "abc", "mississippimississippi",
        "abcabcabd", "no matches here", "", "aabaaabaaab", "ababababca"
    };
    const char* aj[10] = {
        "issi", "aa", "aba", "abcd", "issippi",
        "abcabd", "xyz", "a", "aaab", "abac"
    };
    int ak[10] = { 1, 0, 0, -1, 4, 3, -1, -1, 3, -1 };
    int al[10] = { 2, 3, 3, 0, 2, 1, 0, 0, 2, 0 };
    int am[10][5] = {
        { 1, 4 },{ 0, 1, 2 },{ 0, 2, 4 },{ -1 },{ 4, 15 },
        { 3 },{ -1 },{ -1 },{ 3, 7 },{ -1 }
    };
    int an = 0;
    int r[b];
    long long i;
    int o;

    cout << "\nKMP SEARCH TESTS\n";
    for (int ag = 0; ag < 10; ag++) {
        f(aj[ag], h, ae);
        int ao = m(ai[ag], aj[ag], h, i, o);
        int s = q(ai[ag], aj[ag], h, r, i, o);
        bool ap = s == al[ag] &&
            u(r, am[ag], s);
        bool ah = ao == ak[ag] && ap;
        cout << "Search test " << ag + 1 << ": " << (ah ? "PASS" : "FAIL")
            << " | first = " << ao << " | all = ";
        x(r, s);
        if (ah) an++;
    }
    cout << "Search tests passed: " << an << "/10\n";

    const char aq[] = "mississippimississippi";
    const char ar[] = "issippi";
    f(ar, h, ae);

    cout << "\nVARIANT 5\n";
    cout << "Text: " << aq << "\nPattern: " << ar << "\n";
    cout << "Prefix function: ";
    x(h, c(ar));

    int ao = m(aq, ar, h, i, o);
    cout << "First occurrence: " << ao << "\n";
    cout << "First search comparisons: " << i << "\n";
    cout << "First search prefix shifts: " << o << "\n";

    int s = q(aq, ar, h, r, i, o);
    cout << "All occurrences: ";
    x(r, s);
    cout << "All search comparisons: " << i << "\n";
    cout << "All search prefix shifts: " << o << "\n";

    const char as[] = "abababa";
    const char at[] = "aba";
    f(at, h, ae);
    s = q(as, at, h, r, i, o);
    cout << "\nOVERLAPPING MATCHES\nPositions for abababa / aba: ";
    x(r, s);

    cout << "\nKMP VS DIRECT SEARCH\n";
    const char* au[3] = {
        "aaaaaaaaaaaaaaaaab", "ababababababababac", "mississippimississippi"
    };
    const char* av[3] = { "aaaaab", "ababac", "issippi" };

    for (int ag = 0; ag < 3; ag++) {
        f(av[ag], h, ae);
        int aw = q(au[ag], av[ag], h,
            r, i, o);
        long long ax = i;
        int ay[b];
        long long az;
        int ba = t(au[ag], av[ag],
            ay, az);
        cout << "Example " << ag + 1 << ": " << au[ag]
            << " / " << av[ag] << "\n";
        cout << "KMP comparisons: " << ax
            << ", direct comparisons: " << az << "\n";
        cout << "KMP positions: ";
        x(r, aw);
        cout << "Direct positions: ";
        x(ay, ba);
    }

    const char bb[] = "mississippi";
    const char bc[] = "issippi";
    f(bc, h, ae);
    y(bb, bc, h);

    return 0;
}
