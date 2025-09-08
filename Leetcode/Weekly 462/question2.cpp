class Solution {
    public:
        int sortPermutation(vector<int>& nums) {
            int n = nums.size();
            vector<int> target = nums;
            sort(target.begin(), target.end());
            if (nums == target) return 0;
    
            int maxVal = n - 1;
            int bits = 32 - __builtin_clz(maxVal);
            int ans = 0;
    
            for (int k = n - 1; k >= 1; --k) {
                vector<int> parent(n);
                iota(parent.begin(), parent.end(), 0);
    
                auto find = [&](auto self, int x) -> int {
                    return parent[x] == x ? x : parent[x] = self(self, parent[x]);
                };
                auto unite = [&](int a, int b) {
                    a = find(find, a);
                    b = find(find, b);
                    if (a != b) parent[a] = b;
                };
    
                vector<vector<int>> buckets(bits);
                for (int v = 0; v < n; ++v) {
                    if ((v & k) == k) {
                        for (int b = 0; b < bits; ++b) {
                            if (v & (1 << b)) buckets[b].push_back(v);
                        }
                    }
                }
                // connect inside each bucket
                for (auto &bucket : buckets) {
                    for (int i = 1; i < (int)bucket.size(); ++i) {
                        unite(bucket[0], bucket[i]);
                    }
                }
    
                bool ok = true;
                for (int i = 0; i < n; ++i) {
                    if (find(find, nums[i]) != find(find, target[i])) {
                        ok = false;
                        break;
                    }
                }
                if (ok) return k;
            }
            return 0;
        }
    };
    