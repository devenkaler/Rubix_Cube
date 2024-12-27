#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#define BITVAL(X, index) (X & (1ULL << index))
#define SHIFTRIGHT(X, n)  (X >> n)
#define SHIFTLEFT(X, n)  (X << n)
#define BITREM(X, Y) (X & ~Y)
typedef unsigned long long U64;

using namespace std;

void printBit(U64  n) {
    for (int i = 0; i < 48; i++)  {
        if (BITVAL(n, i)) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
    cout << endl;
}

struct stringInt {
    string s;
    int i;
};

class cube {
    public:
        U64 white = 255ULL;
        U64 red = SHIFTLEFT(255ULL,  8);
        U64 green = SHIFTLEFT(255ULL,  16);
        U64 orange = SHIFTLEFT(255ULL,  24);
        U64 blue = SHIFTLEFT(255ULL,  32);
        U64 yellow = SHIFTLEFT(255ULL,  40);

        map<char, U64> colors = {{'w', this->white}, {'r', this->red}, {'g', this->green}, {'o', this->orange}, {'b', this->blue}, {'y', this->yellow}};
        map<char, int> face_offset = {{'w', 0}, {'r', 8}, {'g', 16}, {'o', 24}, {'b', 32}, {'y', 40}};
        map<int, int> adj_edge = {{1, 5+face_offset['r']}, {3, 7+face_offset['g']}, {5, 1+face_offset['o']}, {7, 3+face_offset['b']},
                                  {41, 5+face_offset['o']}, {43, 3+face_offset['g']}, {45, 1+face_offset['r']}, {47, 7+face_offset['b']},
                                  {15, 1+face_offset['b']}, {11, 1+face_offset['g']}, {31, 5+face_offset['b']}, {27, 5+face_offset['g']}};

        map<int, vector<int>> adj_corner = {{0, {6+face_offset['r'], 2+face_offset['b']}}, {2, {4+face_offset['r'], face_offset['g']}},
                                             {6, {face_offset['o'], 4+face_offset['b']}}, {4, {2+face_offset['o'], 6+face_offset['g']}},
                                             {40, {6+face_offset['o'], 6+face_offset['b']}}, {42, {4+face_offset['o'], 4+face_offset['g']}},
                                             {46, {face_offset['b'], face_offset['r']}}, {44, {2+face_offset['g'], 2+face_offset['r']}}};

        void move(string input) {
            if (input == "F")  { F(); }
            else if (input  == "R") { R(); }
            else if (input  == "L") { L(); }
            else if (input  == "D") { D(); }
            else if (input  == "U") { U(); }
            else if (input  == "B") { B(); }
            else if (input  == "FP") { FP(); }
            else if (input  == "RP") { RP(); }
            else if (input  == "LP") { LP(); }
            else if (input  == "DP") { DP(); }
            else if (input  == "UP") { UP(); }
            else if (input  == "BP") { BP(); }
            else if (input == "scramble") { scramble(); }
            else if (input.substr(0, 4) == "edge") { printBit(getEdge(input.substr(4, 2))); }
            else if (input.substr(0, 6) == "corner") { printBit(getCorner(input.substr(6, 3))); }
            else if (input != "solve") {cout << "BAD(" << input <<")";}
        }

        void printCube() {
            vector<string> w = getFace('w');
            vector<string> r = getFace('r');
            vector<string> g = getFace('g');
            vector<string> o = getFace('o');
            vector<string> b = getFace('b');
            vector<string> y = getFace('y');
            string dflt = "\033[0m";

            cout << dflt << "         [" << r[0] << dflt << "][" << r[1] << dflt << "]["  << r[2] << dflt << "]\n";
            cout << dflt << "         [" << r[7] << dflt << "][" << "\033[31mR" << dflt << "]["  << r[3] << dflt << "]\n";
            cout << dflt << "         [" << r[6] << dflt << "][" << r[5] << dflt << "]["  << r[4] << dflt << "]\n";

            cout << dflt << "[" << b[0] << dflt << "][" << b[1] << dflt << "]["  << b[2] << dflt << "]";;
            cout << dflt << "[" << w[0] << dflt << "][" << w[1] << dflt << "]["  << w[2] << dflt << "]";;
            cout << dflt << "[" << g[0] << dflt << "][" << g[1] << dflt << "]["  << g[2] << dflt << "]\n";
            cout << dflt << "[" << b[7] << dflt << "][" << "\033[34mB" << dflt << "]["  << b[3] << dflt << "]";
            cout << dflt << "[" << w[7] << dflt << "][" << "\033[0mW" << dflt << "]["  << w[3] << dflt << "]";
            cout << dflt << "[" << g[7] << dflt << "][" << "\033[32mG" << dflt << "]["  << g[3] << dflt << "]\n";
            cout << dflt << "[" << b[6] << dflt << "][" << b[5] << dflt << "]["  << b[4] << dflt << "]";;
            cout << dflt << "[" << w[6] << dflt << "][" << w[5] << dflt << "]["  << w[4] << dflt << "]";;
            cout << dflt << "[" << g[6] << dflt << "][" << g[5] << dflt << "]["  << g[4] << dflt << "]\n";

            cout << dflt << "         [" << o[0] << dflt << "][" << o[1] << dflt << "]["  << o[2] << dflt << "]\n";
            cout << dflt << "         [" << o[7] << dflt << "][" << "\033[33mO" << dflt << "]["  << o[3] << dflt << "]\n";
            cout << dflt << "         [" << o[6] << dflt << "][" << o[5] << dflt << "]["  << o[4] << dflt << "]\n";

            cout << dflt << "         [" << y[0] << dflt << "][" << y[1] << dflt << "]["  << y[2] << dflt << "]\n";
            cout << dflt << "         [" << y[7] << dflt << "][" << "\033[93mY" << dflt << "]["  << y[3] << dflt << "]\n";
            cout << dflt << "         [" << y[6] << dflt << "][" << y[5] << dflt << "]["  << y[4] << dflt << "]\n";
        }

        void F() {
           turn('w');
           swap({6, 5, 4}, {0, 7, 6}, {2, 1, 0}, {4, 3, 2}, {'r', 'g', 'o', 'b'});
        }

        void R() {
           turn('g');
           swap({4, 3, 2}, {4, 3, 2}, {4, 3, 2}, {4, 3, 2}, {'w', 'r', 'y', 'o'});
        }

        void L() {
           turn('b');
           swap({0, 7, 6}, {0, 7, 6}, {0, 7, 6}, {0, 7, 6}, {'w', 'o', 'y', 'r'});
        }

        void D() {
            turn('o');
            swap({6, 5, 4}, {6, 5, 4}, {2, 1, 0}, {6, 5, 4}, {'w', 'g', 'y', 'b'});
        }

        void U() {
            turn('r');
            swap({2, 1, 0}, {2, 1, 0}, {6, 5, 4}, {2, 1, 0}, {'w', 'b', 'y', 'g'});
        }

        void B() {
            turn('y');
            swap({6, 7, 0}, {4, 5, 6}, {2, 3, 4}, {0, 1, 2}, {'b', 'o', 'g', 'r'});
        }

        void FP() {
           turn('w', false);
           swap({4, 3, 2}, {2, 1, 0}, {0, 7, 6}, {6, 5, 4}, {'b', 'o', 'g', 'r'});
        }

        void RP() {
           turn('g', false);
           swap({4, 3, 2}, {4, 3, 2}, {4, 3, 2}, {4, 3, 2}, {'o', 'y', 'r', 'w'});
        }

        void LP() {
           turn('b', false);
           swap({0, 7, 6}, {0, 7, 6}, {0, 7, 6}, {0, 7, 6}, {'r', 'y', 'o', 'w'});
        }

        void DP() {
            turn('o', false);
            swap({6, 5, 4}, {2, 1, 0}, {6, 5, 4}, {6, 5, 4}, {'b', 'y', 'g', 'w'});
        }

        void UP() {
            turn('r', false);
            swap({2, 1, 0}, {6, 5, 4}, {2, 1, 0}, {2, 1, 0}, {'g', 'y', 'b', 'w'});
        }

        void BP() {
            turn('y', false);
            swap({0, 1, 2}, {2, 3, 4}, {4, 5, 6}, {6, 7, 0}, {'r', 'g', 'o', 'b'});
        }

        void scramble(int n=50) {
            int r;
            vector<string> moves = {"F", "R", "L", "D", "U", "B", "FP", "RP", "LP", "DP", "UP", "BP"};
            for (int i=0; i<n; i++) {
                r = rand() % 12;
                //cout << moves[r] << " ";
                move(moves[r]);
            }
        }

        U64 getEdge(string edge) {
            U64 res;
            char e1 = edge[0];
            char e2 = edge[1];

            for (int i=1; i<8; i+=2) {
                for (int n: {face_offset['w'], face_offset['y']}) {
                    if ((SHIFTLEFT(1ULL, i+n) | SHIFTLEFT(1ULL, adj_edge[i+n])) & colors[e1]) {
                        if ((SHIFTLEFT(1ULL, adj_edge[i+n]) | SHIFTLEFT(1ULL, i+n)) & colors[e2]) {
                            res = (SHIFTLEFT(1ULL, i+n) & colors[e1]) ? SHIFTLEFT(1ULL, i+n) : SHIFTLEFT(1ULL, adj_edge[i+n]);
                            return res;
                        }
                    }
                }
            }

            for (int i: {3, 7}) {
                for (int n: {face_offset['r'], face_offset['o']}) {
                    if ((SHIFTLEFT(1ULL, i+n) | SHIFTLEFT(1ULL, adj_edge[i+n])) & colors[e1]) {
                        if ((SHIFTLEFT(1ULL, adj_edge[i+n]) | SHIFTLEFT(1ULL, i+n)) & colors[e2]) {
                            res = (SHIFTLEFT(1ULL, i+n) & colors[e1]) ? SHIFTLEFT(1ULL, i+n) : SHIFTLEFT(1ULL, adj_edge[i+n]);
                            return res;
                        }
                    }
                }
            }

            return 0ULL;

        }

        U64 getCorner(string corner) {
            char e1 = corner[0];
            char e2 = corner[1];
            char e3 = corner[2];

            for (int i=0; i<7; i+=2) {
                for (int n: {face_offset['w'], face_offset['y']}) {
                    if ((SHIFTLEFT(1ULL, i+n) | SHIFTLEFT(1ULL, adj_corner[i+n][0]) | SHIFTLEFT(1ULL, adj_corner[i+n][1])) & colors[e1]) {
                        if ((SHIFTLEFT(1ULL, adj_corner[i+n][0]) | SHIFTLEFT(1ULL, i+n) | SHIFTLEFT(1ULL, adj_corner[i+n][1])) & colors[e2]) {
                            if ((SHIFTLEFT(1ULL, adj_corner[i+n][0]) | SHIFTLEFT(1ULL, i+n) | SHIFTLEFT(1ULL, adj_corner[i+n][1])) & colors[e3]) {
                                if (SHIFTLEFT(1ULL, i+n) & colors[e1]) { return SHIFTLEFT(1ULL, i+n); }
                                else if (SHIFTLEFT(1ULL, adj_corner[i+n][0]) & colors[e1]) { return SHIFTLEFT(1ULL, adj_corner[i+n][0]); }
                                return SHIFTLEFT(1ULL, adj_corner[i+n][1]);
                            }
                        }
                    }
                }
            }

            return 0ULL;
        }

    private:

        // from w, y, r, o, b, g
        vector<string> getFace(char face) {
            map<char, string> text_color = {{'w', "\033[0m"}, {'r', "\033[31m"}, {'g', "\033[32m"}, {'o', "\033[33m"}, {'b', "\033[34m"}, {'y', "\033[93m"}, };

            vector<string> res;

            for (int i=0; i<8; i++) {
                for (char c: {'w', 'r', 'g', 'o', 'b', 'y'}) {
                    if (BITVAL(this->colors[c], face_offset[face]+i)) {
                        res.push_back(text_color[c]+'+');
                        break;
                    }
                }
                
            }

            return res;

        }

        void turn(char face, bool clockwise = true) {
            int start = face_offset[face];
            int left = clockwise ? 2 : 6;
            int right = clockwise ? 6 : 2;
            U64 target = SHIFTLEFT(255ULL,  start);
            U64 target_val;

            for (char fs: {'w', 'r', 'g', 'o', 'b', 'y'}) {
                target_val = (colors[fs] & target);
                colors[fs] = ((colors[fs] &  ~target) | ((SHIFTLEFT(target_val, left) & target) | (SHIFTRIGHT(target_val, right) & target)));
            }
        }

        void swap(vector<int> a, vector<int> b, vector<int> c, vector<int> d, vector<char> faces) {
            for (char fs: {'w', 'r', 'g', 'o', 'b', 'y'}) {
                for (int i=0; i<3; i++) {
                    bool a_val = BITVAL(colors[fs], a[i]+face_offset[faces[0]]);
                    bool b_val = BITVAL(colors[fs], b[i]+face_offset[faces[1]]);
                    bool c_val = BITVAL(colors[fs], c[i]+face_offset[faces[2]]);
                    bool d_val = BITVAL(colors[fs], d[i]+face_offset[faces[3]]);

                    if (a_val) {
                        colors[fs] = BITREM(colors[fs], (1ULL << a[i]+face_offset[faces[0]]));
                    }
                    if (b_val) {
                        colors[fs] = BITREM(colors[fs], (1ULL << b[i]+face_offset[faces[1]])); 
                    }
                    if (c_val) {
                        colors[fs] = BITREM(colors[fs], (1ULL << c[i]+face_offset[faces[2]]));
                    }
                    if (d_val) {
                        colors[fs] = BITREM(colors[fs], (1ULL << d[i]+face_offset[faces[3]]));
                    }

                    if (a_val) {
                        colors[fs] = (colors[fs] | (1ULL << b[i]+face_offset[faces[1]]));
                    }
                    if (b_val) {
                        colors[fs] = (colors[fs] | (1ULL << c[i]+face_offset[faces[2]]));
                    }
                    if (c_val) {
                        colors[fs] = (colors[fs] | (1ULL << d[i]+face_offset[faces[3]]));
                    }
                    if (d_val) {
                        colors[fs] = (colors[fs] | (1ULL << a[i]+face_offset[faces[0]]));
                    }

                }
            }
        }
};

class solve {
    public: 
        vector<string> moves;
        cube curr;
        map<char, int> f_off = curr.face_offset;
        solve(cube c) {
            curr = c;
        }

        vector<string> run() {
            vector<string> res;

            vector<string> cr = cross();
            cout << "Solved Cross in: " << cr.size() << " moves.\n";
            for (string mv: cr) {
                curr.move(mv);
                cout << mv << ", ";
            }
            cout << "\n";
            res.insert(res.end(), cr.begin(), cr.end());

            vector<string> cn = corners();
            cout << "Solved Corners in: " << cn.size() << " moves.\n";
            for (string mv: cn) {
                curr.move(mv);
                cout << mv << ", ";
            }
            cout << "\n";
            res.insert(res.end(), cn.begin(), cn.end());

            vector<string> sl = secLayer();
            cout << "Solved Second Layer in: " << sl.size() << " moves.\n";
            for (string mv: sl) {
                curr.move(mv);
                cout << mv << ", ";
            }
            cout << "\n";
            res.insert(res.end(), sl.begin(), sl.end());

             vector<string> ycr = yCross();
            cout << "Solved top Layer Cross in: " << ycr.size() << " moves.\n";
            for (string mv: ycr) {
                curr.move(mv);
                cout << mv << ", ";
            }
            cout << "\n";
            res.insert(res.end(), ycr.begin(), ycr.end());

            return res;
        }

        vector<string> cross() {
            cout << "Solving for the white cross: \n\n";
            vector<string> res_smallest;
            int smallest_size = 100;
            vector<string> cr;
            cout << "Trying to find a solution less than 5 moves (trivial)\n\n";
            for (int i=0; i<5; i++) {
                cr = crossRec(curr, {}, i, {{"wr", 1}, {"wg", 3}, {"wo",  5}, {"wb", 7}});
                if (cr.empty()) {
                    return cr;
                } else if (cr[0] != "bad") {
                    return cr;
                }
            }

            cout << "Finding alternate solution by placing edges one at a time: \n\n";
            vector<stringInt> req_total = {{"wr", 1}, {"wg", 3}, {"wo",  5}, {"wb", 7}};
            vector<vector<int>> perms = allPerms(4);
            for (vector<int> perm: perms) {
                vector<string> res = {};
                vector<stringInt> req = {};
                cube curr_(this->curr);
                for (int p: perm) {
                    req.push_back(req_total[p]);
                    for (int i=0; i<5; i++) {
                        cr = crossRec(curr_, {}, i, req);
                        if (cr.empty()) {
                            break;
                        } else if (cr[0] != "bad") {
                            break;
                        }
                    }
                    for (string m: cr) {
                        curr_.move(m);
                    }
                    res.insert(res.end(), cr.begin(), cr.end());
                }

                if (!cr.empty() && cr[0] == "bad") {
                    continue;
                }

                if (res.size() < smallest_size) { 
                    res_smallest = res; 
                    smallest_size = res.size();
                }

            }

            return res_smallest;
        }

        vector<string> corners() {
            vector<string> res, res_smallest;
            int smallest_size = 100;
            map<string, int> req = {{"wrb", 0}, {"wrg", 2}, {"wob", 6}, {"wog", 4}};

            map<U64, vector<string>> cpos0 = {{SHIFTLEFT(1ULL, 0), {"LP", "BP", "L"}},
                                              {SHIFTLEFT(1ULL, 2), {"R", "B", "RP"}},
                                              {SHIFTLEFT(1ULL, 6), {"L", "BP", "LP"}},
                                              {SHIFTLEFT(1ULL, 4), {"RP", "B", "R"}}};

            map<U64, vector<string>> cpos1 = {{SHIFTLEFT(1ULL, 6+f_off['r']), {"LP", "B", "L"}},
                                              {SHIFTLEFT(1ULL, 4+f_off['r']), {"R", "BP", "RP"}},
                                              {SHIFTLEFT(1ULL, f_off['o']), {"L", "BP", "LP"}},
                                              {SHIFTLEFT(1ULL, 2+f_off['o']), {"RP", "B", "R"}},
                                              {SHIFTLEFT(1ULL, f_off['g']), {"UP", "B", "U"}},
                                              {SHIFTLEFT(1ULL, 6+f_off['g']), {"D", "BP", "DP"}},
                                              {SHIFTLEFT(1ULL, 2+f_off['b']), {"U", "BP", "UP"}},
                                              {SHIFTLEFT(1ULL, 4+f_off['b']), {"DP", "B", "D"}}};

            map<string, vector<string>> cpos2  = {{"wrg", {"R", "BP", "RP", "UP", "B", "B", "U"}},
                                               {"wrb", {"LP", "B", "L", "U", "B", "B", "UP"}},
                                               {"wog", {"RP", "B", "R", "D", "B", "B", "DP"}},
                                               {"wob", {"L", "BP", "LP", "DP", "B", "B", "D"}}};

            map<U64, vector<string>> cpos3 = {{SHIFTLEFT(1ULL, f_off['r']), {"U", "B", "UP"}},
                                              {SHIFTLEFT(1ULL, 2+f_off['r']), {"UP", "BP", "U"}},
                                              {SHIFTLEFT(1ULL, 4+f_off['o']), {"D", "B", "DP"}},
                                              {SHIFTLEFT(1ULL, 6+f_off['o']), {"DP", "BP", "D"}},
                                              {SHIFTLEFT(1ULL, 2+f_off['g']), {"R", "BP", "RP"}},
                                              {SHIFTLEFT(1ULL, 4+f_off['g']), {"RP", "BP", "R"}},
                                              {SHIFTLEFT(1ULL, f_off['b']), {"LP", "BP", "L"}},
                                              {SHIFTLEFT(1ULL, 6+f_off['b']), {"L", "B", "LP"}}};

            map<U64, string> cpos3_check = {{SHIFTLEFT(1ULL, f_off['r']), "wrb"},
                                                {SHIFTLEFT(1ULL, 2+f_off['r']), "wrg"},
                                                {SHIFTLEFT(1ULL, 4+f_off['o']), "wog"},
                                                {SHIFTLEFT(1ULL, 6+f_off['o']), "wob"},
                                                {SHIFTLEFT(1ULL, 2+f_off['g']), "wrg"},
                                                {SHIFTLEFT(1ULL, 4+f_off['g']), "wog"},
                                                {SHIFTLEFT(1ULL, f_off['b']), "wrb"},
                                                {SHIFTLEFT(1ULL, 6+f_off['b']), "wob"}};

            cout << "\nFinding solution to white corners:\n\n";

            vector<vector<int>> perms = allPerms(4);
            vector<string> req_corners = {"wrb", "wrg", "wob", "wog"};
            for (vector<int> p: perms) {
                res = {};
                cube curr_(this->curr);
                for (string c:vector<string> {req_corners[p[0]], req_corners[p[1]], req_corners[p[2]], req_corners[p[3]]}) {
                    U64 cpos;
                    for (int i=0; i<=100; i++) {
                        cpos = curr_.getCorner(c);
                        if (cpos & SHIFTLEFT(1ULL, req[c])) { 
                            break; 

                        } else if (cpos3_check.find(cpos) != cpos3_check.end() && cpos3_check[cpos] == c) {
                            for (string mv: cpos3[cpos]) { 
                                curr_.move(mv); 
                                res.push_back(mv);
                                if (i > 60) { cout << mv;  }
                            }

                        } else if (cpos0.find(cpos) != cpos0.end()) { //on white face
                            for (string mv: cpos0[cpos]) { 
                                curr_.move(mv); 
                                res.push_back(mv);
                                if (i > 60) { cout << mv;  }
                            }
                            
                        } else if (SHIFTLEFT(1ULL, (6-req[c])+f_off['y']) & cpos) { //on yellow face
                            for (string mv: cpos2[c]) { 
                                curr_.move(mv); 
                                res.push_back(mv);
                                if (i > 60) { cout << mv;  }
                            }

                        } else if (cpos1.find(cpos) != cpos1.end() && cpos != 274877906944) {
                            for (string mv: cpos1[cpos]) { 
                                curr_.move(mv); 
                                res.push_back(mv);
                                if (i > 60) { cout << mv;  }
                            }

                        } else if (i == 100) {
                            cout << c;
                            curr_.printCube();
                            return {"bad"};

                        } else {
                            if (i > 60) { cout << "B";  }
                            res.push_back("B");
                            curr_.move("B");

                        }
                    }
                }
                
                if (res.size() < smallest_size) {
                    res_smallest = res;
                    smallest_size = res.size();
                }

            }

            return res;
        }

        vector<string> secLayer() {
            vector<string> res, res_smallest;
            int smallest_size = 100;

            map<string, U64> req   = {{"rb", SHIFTLEFT(1ULL, 7+f_off['r'])}, {"rg", SHIFTLEFT(1ULL, 3+f_off['r'])},
                                      {"ob", SHIFTLEFT(1ULL, 7+f_off['o'])}, {"og", SHIFTLEFT(1ULL, 3+f_off['o'])},
                                      {"br", SHIFTLEFT(1ULL, 1+f_off['b'])}, {"gr", SHIFTLEFT(1ULL, 1+f_off['g'])},
                                      {"bo", SHIFTLEFT(1ULL, 5+f_off['b'])}, {"og", SHIFTLEFT(1ULL, 5+f_off['g'])}};

            map<string, vector<string>> epos1 = {{"go", {"D", "BP", "DP", "BP", "RP", "B", "R"}}, {"bo", {"DP", "B", "D", "B", "L", "BP", "LP"}},
                                              {"rb", {"LP", "B", "L", "B", "U", "BP", "UP"}}, {"ob",  {"L", "BP", "LP", "BP", "DP", "B", "D"}},
                                              {"rg", {"R", "BP", "RP", "BP", "UP", "B", "U"}}, {"og", {"RP", "B", "R", "B", "D", "BP", "DP"}},
                                              {"br", {"U", "BP", "UP", "BP", "LP", "B", "L"}}, {"gr", {"UP", "B", "U", "B", "R", "BP", "RP"}}};

            map<U64, vector<string>>  epos1_check = {{SHIFTLEFT(1ULL, 1+f_off['r']), {"go", "bo"}},
                                                        {SHIFTLEFT(1ULL, 3+f_off['g']), {"rb", "ob"}},
                                                        {SHIFTLEFT(1ULL, 7+f_off['b']), {"rg", "og"}},
                                                        {SHIFTLEFT(1ULL, 5+f_off['o']), {"br", "gr"}}};

            map<U64, vector<string>> epos2 = {{SHIFTLEFT(1ULL, 3+f_off['r']), epos1["rg"]}, {SHIFTLEFT(1ULL, 7+f_off['r']), epos1["rb"]},
                                              {SHIFTLEFT(1ULL, 3+f_off['o']), epos1["og"]}, {SHIFTLEFT(1ULL, 7+f_off['o']), epos1["ob"]},
                                              {SHIFTLEFT(1ULL, 1+f_off['g']), epos1["rg"]}, {SHIFTLEFT(1ULL, 1+f_off['b']), epos1["rb"]},
                                              {SHIFTLEFT(1ULL, 5+f_off['g']), epos1["og"]}, {SHIFTLEFT(1ULL, 5+f_off['b']), epos1["ob"]}};

            vector<vector<int>> perms = allPerms(4);
            vector<string> req_edges = {"rb", "rg", "ob", "og"};
            
            for (vector<int> perm: perms) {
                cube curr_(this->curr);
                res = {};
                for (string e: {req_edges[perm[0]], req_edges[perm[1]], req_edges[perm[2]], req_edges[perm[3]]}) {
                    for (int i=0; i<100; i++) {
                        U64 epos = curr_.getEdge(e);
                        if (SHIFTRIGHT(epos, 40)) {
                            reverse(e.begin(), e.end());

                        } else if (req[e] == epos) {
                            break;

                        } else if (epos2.find(epos) != epos2.end()) {
                            for (string mv: epos2[epos]) {
                                curr_.move(mv);
                                res.push_back(mv);
                            }

                        } else if (epos1_check.find(epos) != epos1_check.end()) {
                            if (epos1_check[epos][0] == e || epos1_check[epos][1] == e) {
                                for (string mv: epos1[e]) {
                                    curr_.move(mv);
                                    res.push_back(mv);
                                }

                            } else {
                                curr_.move("B");
                                res.push_back("B");

                            }
                        }  else {
                            curr_.move("B");
                            res.push_back("B");

                        }
                    }
                }

                if (res.size() < smallest_size) {
                    res_smallest = res;
                    smallest_size = res.size();
                }
            }

            return res;
        }

    vector<string> yCross() {
        cube curr_(this->curr);
        vector<string> res;
        U64 ypos_curr;
        U64 all = (1ULL << 7) | (1ULL << 5) | (1ULL << 3) | (1ULL << 1);

        map<U64, vector<string>> ypos = {{0ULL, {"U", "B", "R", "BP", "RP", "UP", "B", "U", "R", "B", "RP", "BP", "UP"}}, 
                                         {(1ULL << 1) | (1ULL << 7), {"U", "B", "R", "BP", "RP", "UP"}},
                                         {(1ULL << 1) | (1ULL << 5), {"U", "R", "B", "RP", "BP", "UP"}}};

        for (int i=0; i<10; i++) {
            U64 ypos_curr = (SHIFTRIGHT(curr_.colors['y'], 40) & all);
            
            if (ypos.find(ypos_curr) != ypos.end()) {
                for (string mv: ypos[ypos_curr]) {
                    res.push_back(mv);
                    curr_.move(mv);
                }
            } else if (ypos_curr != all){
                res.push_back("B");
                curr_.move("B");
            } else {
                break;
            }
        }

        return res;
    }
    
    private:

        vector<vector<int>> allPerms(int n) {
            vector<int> n_vec;
            vector<vector<int>> res;
            for (int i=0; i<n; i++) {
                n_vec.push_back(i);
            }

            do {
                res.push_back(n_vec);
            } while(next_permutation(n_vec.begin(), n_vec.end()));

            return res;

        }

        vector<string> crossRec(cube ctemp, vector<string> moves, int breadth, vector<stringInt> req) {
            bool ret = true;
            for (stringInt r: req) {
                if (ctemp.getEdge(r.s) != SHIFTLEFT(1ULL, r.i)) {
                    ret = false;
                    break;
                }
            }
            if (ret == true) { return moves; }

            if (moves.size() < breadth) {
                for (string m: {"F", "R", "L", "D", "U", "B", "FP", "RP", "LP", "DP", "UP", "BP"}) {
                    if (!moves.empty()) {;
                        if (moves.back() == m+"P"  || moves.back()+"P"  == m) {
                            continue;
                        } else if (moves.size() > 2) {
                            if (moves[moves.size()-2] == moves.back() && moves.back() == m) {
                                continue;
                            }
                        }
                    } 
                    vector<string> moves_(moves);
                    moves_.push_back(m);
                    cube ctemp_(ctemp);
                    ctemp_.move(m);
                    vector<string> cr = crossRec(ctemp_, moves_, breadth, req);
                    if (cr[0] == "bad") {
                        continue;
                    } else {
                        return cr;
                    }
                }
            }
            
            return {"bad"};
        }



};

int main() {
    cube c;
    string input;
    
    do {
        c.printCube();
        cout << "\nEnter move: ";
        cin >> input;
        if (input == "solve") {
            solve s(c);
            vector<string> sol = s.run();
            for (string mv: sol) {
                c.move(mv);
            }
        }
        c.move(input);
    } while (input != "X");

    return 1;
}
