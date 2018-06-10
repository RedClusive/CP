#include <bits/stdc++.h>

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define endl '\n'
#define pii pair <int, int>
#define pll pair <ll, ll>
#define pld pair <ld, ld>

using namespace std;

//V CODE_BEGIN V

struct min_stack { //Ñòåê ñ ïîääåðæêîé ìèíèìàëüíîãî ýëåìåíòà òèïà int è ñîõðàíåíèåì ïîðÿäêà
    stack <int> v, m;
    void push(int x) {
        v.push(x);
        m.push(m.empty() ? x : min(m.top(), x));
    }
    int pop() {
        v.pop();
        m.pop();
    }
    int top() {
        return v.top();
    }
    int mn() {
        return m.top();
    }
    bool empty() {
        return v.empty();
    }
};

struct max_stack { //Ñòåê ñ ïîääåðæêîé ìàêñèìàëüíîãî ýëåìåíòà òèïà int è ñîõðàíåíèåì ïîðÿäêà
    stack <int> v, m;
    void push(int x) {
        v.push(x);
        m.push(m.empty() ? x : max(m.top(), x));
    }
    void pop() {
        v.pop();
        m.pop();
    }
    int top() {
        return v.top();
    }
    int mx() {
        return m.top();
    }
    bool empty() {
        return v.empty();
    }
};

struct min_max_queue{ //Î÷åðåäü ñ ïîääåðæêîé ìèíèìàëüíîãî è ìàêñèìàëüíîãî ýëåìåíòîâ òèïà int è ñîõðàíåíèåì ïîðÿäêà
    min_stack in1, out1;
    max_stack in2, out2;
    void push(int x) {
        in1.push(x);
        in2.push(x);
    }
    void pop() {
        if (out1.empty()) {
            while (!in1.empty()) {
                out1.push(in1.top());
                in1.pop();
            }
        }
        out1.pop();
        if (out2.empty()) {
            while (!in2.empty()) {
                out2.push(in2.top());
                in2.pop();
            }
        }
        out2.pop();
    }
    int mn() {
        int res1 = 1e9 + 7;
        if (!in1.empty()) res1 = in1.mn();
        int res2 = 1e9 + 7;
        if (!out1.empty()) res2 = out1.mn();
        return min(res1, res2);
    }
     int mx() {
        int res1 = -1e9 - 7;
        if (!in2.empty()) res1 = in2.mx();
        int res2 = -1e9 - 7;
        if (!out2.empty()) res2 = out2.mx();
        return max(res1, res2);
    }
};
//X CODE_END X

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int x = 228;
    int y = 1337;
    int z = 1488;
    min_max_queue q; // Ïóñòàÿ î÷åðåäü
    q.push(x); // Äîáàâëåíèå ýëåìåíòà.
    cout << q.mn() << ' ' << q.mx() << endl; // Çàïðîñ íà ìèíèìàëüíûé è ìàêñèìàëüíûé ýëåìåíòû. Ðåçóëüòàò: 228 228
    q.push(y);
    cout << q.mn() << ' ' << q.mx() << endl; // Ðåçóëüòàò: 228 1337
    q.push(z);
    cout << q.mn() << ' ' << q.mx() << endl; // Ðåçóëüòàò: 228 1488
    return 0;
}
