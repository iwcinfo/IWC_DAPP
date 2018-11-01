#include <contracts.hpp>
void table::create(const account_name account,
		   const string& type,
		   const string& userid,
		   const string& transid,
		   uint64_t transtime,
		   const string& content,
		   uint32_t amount,
		   const string& party
		   ) {
  require_auth(account);
  profile_tablet profilet(_self, _self);
  profilet.emplace(account, [&](auto& p) {
      p.account = account;
      p.type = type;
      p.userid = userid;
      p.transid = transid;
      p.transtime = transtime;
      p.content = content;
      p.amount = amount;
      p.party = party;
    });
}

void table::update(const account_name account,
                   const string& type,
                   const string& userid,
                   const string& transid,
                   uint64_t transtime,
                   const string& content,
                   uint32_t amount,
                   const string& party
                   ) {
  require_auth(account);
  profile_tablet profilet(_self, _self);
  auto itr = profilet.find(account);
  
  profilet.modify(itr, account, [&](auto& p) {
      p.account = account;
      p.type = type;
      p.userid = userid;
      p.transid= transid;
      p.transtime = transtime;
      p.content= content;
      p.amount = amount;
      p.party =party;
    });
}

void table::remove(const account_name account) {
  require_auth(account);
  profile_tablet profilet(_self, _self);
  auto itr = profilet.find(account);
  eosio_assert(itr != profilet.end(), "No Profile");
  profilet.erase(itr);
}
