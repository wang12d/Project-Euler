#include <bits/stdc++.h>

using namespace std;

int digits[] = {1, 2 ,3, 4, 5, 6, 7, 8, 9};
bool bad_inds[100000];

bool is_prime(int n)
{
    long i;
    if (n == 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (i = 3; i*i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

void preety_print(vector<int> vec)
{
    vector<int>::iterator end = vec.end();
    printf("{ ");
    for (vector<int>::iterator it = vec.begin(); it != end; ++it) {
        printf("%d%c", *it, (it+1 == end ? ' ' : ','));
    }
    printf("}\n");
}

vector<vector<int> > handle_recur(vector<vector<int> > pairs, int val)
{
    vector<vector<int> >::iterator end = pairs.end();
    vector<vector<int> > res;

    for (vector<vector<int> >::iterator it = pairs.begin(); it != end; ++it) {
        vector<int>::iterator j_end = (*it).end();
        int tmp;
        for (vector<int>::iterator j = (*it).begin(); j != j_end; ++j) {
            tmp = *j;
            *j = tmp * 10 + val;
            res.push_back((*it));
            *j = tmp;
        }
        vector<int> ps (*it);
        ps.push_back(val);
        res.push_back(ps);
    }

    return res;
}

vector<vector<int> > factor_pairs()
{

    vector<vector<int> > init;
    vector<int> i;
    i.push_back(digits[0]);
    init.push_back(i);

    for (int j = 1; j < 9; ++j) {
        init = handle_recur(init, digits[j]);
    }
    
    return init;
}

vector<int> number_to_vec(int num)
{
    vector<int> res;
    while (num) {
        res.push_back(num % 10);
        num /= 10;
    }

    return res;
}

vector<vector<int> > filter_vect(vector<vector<int> > vec)
{
    int i = 0;
    vector<vector<int> >::iterator end = vec.end();

    for (vector<vector<int> >::iterator it = vec.begin(); it != end; ++it, ++i) {
        vector<int>::iterator j_end = (*it).end();
        for (vector<int>::iterator j = (*it).begin(); j != j_end; ++j) {
            if (((*j) != 3 && (*j) % 3 == 0) || (*j) == 1) {
                bad_inds[i] = true;
                break;
            }
        }
    }

    return vec;
}

int vec_to_number(vector<int> vec)
{
    int res = 0;
    vector<int>::iterator end = vec.end();
    for (vector<int>::iterator it = vec.begin(); it != end; ++it) {
        res *= 10;
        res += (*it);
    }
    return res;
}


vector<vector<int> > help_rec(vector<vector<int> > sour, int size, int ind, vector<int> nums, vector<vector<int> > dest)
{
    if (size < 0) {
        return dest;
    }
    if (ind == size) {
        vector<int> vec = sour[ind];
        int end = vec.size();
        for (int i = 0; i < end; ++i) {
            nums.push_back(vec[i]);
            dest.push_back(nums);
            nums.pop_back();
        }
        return dest;
    }
    else {
        vector<int> vec = sour[ind];
        int end = vec.size();
        for (int i = 0; i < end; ++i) {
            nums.push_back(vec[i]);
            dest = help_rec(sour, size, ind+1, nums, dest);
            nums.pop_back();
        }
        return dest;
    }
}


// 从每个vector中的元素中生成一个vector
vector<vector<int> > generate_vect(vector<vector<int> > all_vectors)
{
    int size = all_vectors.size() - 1;
    vector<vector<int> > res;
    vector<int> nums;
    return help_rec(all_vectors, size, 0, nums, res);
}

int main(int argc, char **argv)
{
    vector<vector<int> > all_lists = filter_vect(factor_pairs());

    int size = all_lists.size();

    vector<vector<int> > all_prime_lst;
    vector<vector<int> > find_combs;
    for (int i = 0; i < size; ++i) {
        if (bad_inds[i]) {
            continue;
        }
        vector<int> lst = all_lists[i];
        int lsz = lst.size();
        // 从每次数字中可能的排列生成素数，然后在将它们一个一个的组合
        vector<vector<int> > all_prime_combs;
        for (int j = 0; j < lsz; j++) {
            int init = lst[j];
            vector<int> primes;
            vector<int> numlst = number_to_vec(lst[j]);
            sort(numlst.begin(), numlst.end());
            bool has_prime = false;
            do {
                int n = vec_to_number(numlst);
                if (is_prime(n)) {
                    has_prime = true;
                    primes.push_back(n);
                }
            } while (next_permutation(numlst.begin(), numlst.end()));
            if (has_prime) all_prime_combs.push_back(primes);
        }
        // 如果有些组合生成不了素数，那么它们的长度将会小于其先前的长度
        if (lsz == all_prime_combs.size()) {
            vector<vector<int> > all_primes = generate_vect(all_prime_combs);
            find_combs.insert(find_combs.end(), all_primes.begin(), all_primes.end());
        }
    }

    int prime_size = find_combs.size();
    printf("the total number is: %d\n", prime_size);
}
