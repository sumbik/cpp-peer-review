#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

class Domain {
    public:
        Domain(string domain_name){
            reverse(domain_name.begin(), domain_name.end());            
            reversed_domain_name_ = domain_name + '.';
        }

        bool operator==(const Domain& other_domain) const{
            return reversed_domain_name_ == other_domain.reversed_domain_name_;
        }

        bool IsSubDomain(const Domain& parent_domain) const{
            if (GetDomainName() == parent_domain.GetDomainName()) {
                return false;
            }
            if (parent_domain.GetDomainName().size() >= GetDomainName().size()){
                return false;
            }
            if (GetDomainName().substr(0, parent_domain.GetDomainName().size()) == parent_domain.GetDomainName()) {
                return true;
            }
            return false;
        }

        string_view GetDomainName() const{   
            return string_view(reversed_domain_name_);
        }

    private:
        string reversed_domain_name_;
};

class DomainChecker {
public:
    template<typename It>
    DomainChecker(It begin, It end){
        for (It it =begin; it != end; ++it){
            forbiden_domains_.push_back(*it);
        }
        sort(forbiden_domains_.begin(), forbiden_domains_.end(),[] (Domain lhs, Domain rhs)
            {return lexicographical_compare(lhs.GetDomainName().begin(), lhs.GetDomainName().end(), rhs.GetDomainName().begin(), rhs.GetDomainName().end());
             });
        auto subs = unique(forbiden_domains_.begin(), forbiden_domains_.end(), [] (Domain lhs, Domain rhs){
            return rhs.IsSubDomain(lhs);
        });
        forbiden_domains_.erase(subs, forbiden_domains_.end());
        for (const Domain& dom : forbiden_domains_){
            forbiden_names_.push_back(dom.GetDomainName());
        }
    }
    
    bool IsForbidden(const Domain& domain){
        string_view name = domain.GetDomainName();
        auto it = upper_bound(forbiden_names_.begin(), forbiden_names_.end(), name);
        if (it == forbiden_names_.begin()){
            return false;
        }
        --it;
        if (*it == name) return true;
        if ((*it).size() >= name.size()) {
            return false;
        }
        if ( name.substr(0, (*it).size()) == *it){
            return true;
        }
        return false;
    }

private:    
    vector<Domain> forbiden_domains_;
    vector<string_view> forbiden_names_;
};

vector<Domain> ReadDomains(istream& input, size_t count){
    vector<Domain> result;
    string s;
    for (size_t i = 0; i < count; ++i){
        getline(input, s);
        Domain new_domain(s);
        result.push_back(new_domain);
    }
    return result;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}