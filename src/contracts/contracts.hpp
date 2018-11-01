#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

using namespace eosio;
using std::string;

class table : public contract {
public:
  table(account_name self) : contract(self) {} // class constructor                                   //@abi action                                                                                                                     
  void create(const account_name account,
	      const string& type,
	      const string& userid,
	      const string& transid,
	      uint64_t transtime,
	      const string& content,
	      uint32_t amount,
              const string& party
	      );

  //@abi action                                                                                     
  void update(const account_name account,
	      const string& type,
	      const string& userid,
	      const string& transid,
	      uint64_t transtime,
	      const string& content,
	      uint32_t amount,
              const string& party
	      );
                                
  void remove(const account_name account);
private:
  //@abi table profiles i64                                                                                                         
  struct profilet {
    account_name account;
    string type;
    string userid;
    string transid;
    uint64_t transtime;
    string content;
    uint32_t amount;
    string party;
    account_name primary_key() const {
      return account;
    }
    EOSLIB_SERIALIZE(profilet, (account)(type)(userid)(transid)(transtime)(content)(amount)(party))
  };
  //initialize the table                                                                                                            
  typedef eosio::multi_index<N(profilest), profilet> profile_tablet;
};

EOSIO_ABI(table, (create)(update)(remove))


