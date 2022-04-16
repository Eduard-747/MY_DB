#ifndef CRUD_H
#define CRUD_H

#include "../parser/parser.h"

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

namespace myl {

  /****************************************************************************** 
  the transmitted class must have this functions: 
  ctor(string)                        | ctor(string, vector<string>)
  string get_DataBase_name() const    | void delete_table(string)
  string get_table(string) const      | void delete_info(string, int)
  string get_info(string, int) const  | void delete_DB()
  string get_DB() const               | int get_table_size(string) const 
  void set_table(string)              | void change_info(string, int, string)
  void set_info(string, int, string)  |

  hash function and operator==
  ******************************************************************************/
  template <class DB, class hash>
  class CRUD
  {
  public:
    CRUD();
    void creat_DB(const std::string&);
    void creat_DB(const std::string&, const std::vector<std::string>&);
    void push_info(const std::string&, const std::string&, const std::string&);
    void change_info(const std::string&, const std::string&, int, const std::string&);
    void set_table(const std::string&, const std::vector<std::string>&);

    std::string get_table(const std::string&,const std::string&) const;
    std::string get_info(const std::string&, const std::string&, int) const; 
    std::string get_DB(const std::string&) const;
    
    void delete_table(const std::string&, const std::string&);
    void delete_info(const std::string&, const std::string&, int);
    void delete_DB(const std::string&);
    void generate_DB(const DB&);
  private:
    void open_file_input(std::ifstream&, const std::string&);
    void push_db_name_in_sfile(const std::string&);
    void delete_db_name_in_sfile(const std::string&);
  private:
    std::unordered_map<std::string, DB, hash> dbs;
  };

} // myl

template <class DB, class hash>
void myl::CRUD<DB,hash>::delete_db_name_in_sfile(const std::string& db_name)
{
  std::vector<std::string> names;
  std::ifstream ifile;
  open_file_input(ifile, "./.DBnames/names.txt");

  std::string str;
  while(!ifile.eof())
  {
    str.clear();
    ifile >> str;
    if(str != db_name && !str.empty()) 
      names.push_back(str);
  }

  ifile.close();
  std::ofstream ofile;
  ofile.open("./.DBnames/names.txt");

  for(const auto& name: names)
    ofile << name << std::endl;
  ofile.close();
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::push_db_name_in_sfile(const std::string& db_name)
{
  std::ifstream ifile;
  open_file_input(ifile, "./.DBnames/names.txt");
  std::string str;
  while(!ifile.eof())
  {
    ifile >> str;
    if(str == db_name) return;
  }
  ifile.close();

  std::ofstream ofile;
  ofile.open("./.DBnames/names.txt", std::ios::app);
  ofile << db_name << std::endl;
  ofile.close();
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::open_file_input(std::ifstream& ifile, const std::string& fileName)
{
  ifile.open(fileName);

  if(!ifile.is_open()) {
    std::cerr << fileName << std::endl;
    std::cerr << "file is not open" << std::endl;
    exit(0);
  }
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::set_table(const std::string& DB_name, const std::vector<std::string>& table_names)
{
  auto& db = dbs.at(DB_name);
  for(const auto& t_name: table_names)
  {
    db.set_table(t_name);
  }
  generate_DB(db);
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::delete_table(const std::string& DB_name, const std::string& table_name)
{
  auto & db = dbs.at(DB_name);
  db.delete_table(table_name);
  generate_DB(db);
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::delete_info(const std::string& DB_name, const std::string& table_name, int count)
{
  auto & db = dbs.at(DB_name);
  db.delete_info(table_name, count);
  generate_DB(db);
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::delete_DB(const std::string& DB_name) 
{
  dbs.erase(DB_name);
  delete_db_name_in_sfile(DB_name);
}

template <class DB, class hash>
std::string myl::CRUD<DB,hash>::get_DB(const std::string& DB_name) const
{
  auto & db = dbs.at(DB_name);
  return db.get_DB();
}

template <class DB, class hash>
std::string myl::CRUD<DB,hash>::get_info(const std::string& DB_name, const std::string& table_name, int count) const
{
  auto & db = dbs.at(DB_name);
  return db.get_info(table_name, count);
}

template <class DB, class hash>
std::string myl::CRUD<DB,hash>::get_table(const std::string& DB_name, const std::string& table_name) const
{
  auto & db = dbs.at(DB_name);
  return db.get_table(table_name);
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::push_info(const std::string& DB_name, const std::string& table_name, const std::string& info)
{
  auto & db = dbs.at(DB_name);
  db.set_info(table_name, db.get_table_size(table_name), info);
  generate_DB(db);
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::change_info(const std::string& DB_name, const std::string& table_name, int count, const std::string& info)
{
  auto & db = dbs.at(DB_name);
  db.change_info(table_name, count, info);
  generate_DB(db);
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::generate_DB(const DB& db)
{
  std::ofstream ofile;
  ofile.open("./DataBaseTxt/" + db.get_DataBase_name());
  ofile << db.get_DB();
  ofile.close();
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::creat_DB(const std::string& DB_name,const std::vector<std::string>& tables)
{
  DB db(DB_name, tables);
  dbs.emplace(DB_name, db);
  push_db_name_in_sfile(DB_name);
  generate_DB(db);
}

template <class DB, class hash>
void myl::CRUD<DB,hash>::creat_DB(const std::string& DB_name)
{
  DB db(DB_name);
  dbs.emplace(DB_name, db);
  push_db_name_in_sfile(DB_name);
  generate_DB(db);
}

template <class DB, class hash>
myl::CRUD<DB,hash>::CRUD()
{
  std::vector<std::string> files_names;
  std::ifstream ifile;

  open_file_input(ifile, "./.DBnames/names.txt");

  std::string file_name;
  while(!ifile.eof())
  {
    file_name.clear();
    ifile >> file_name;
    files_names.push_back(file_name);
  }
  
  
  ifile.close();
  file_name = "./DataBaseTxt/" ;

  std::string str;
  Parser pars;

  for(int i {}; i < files_names.size() - 1; ++i)
  {
    open_file_input(ifile, file_name + files_names[i]);
    DB tmp_db_obj(files_names[i]);

    while(!ifile.eof())
    {
      std::getline(ifile, str);
      pars.parse_code(str);
      std::vector<std::string> tokens = pars.get_tokens();
      if(!tokens.empty())
      {
        tmp_db_obj.set_table(tokens[0]);

        for(int j = 2; j < tokens.size(); ++j)
        {
          tmp_db_obj.set_info(tokens[0], j - 2, tokens[j]);
        }
      }
    }

    dbs.emplace(tmp_db_obj.get_DataBase_name(),tmp_db_obj);
    ifile.close();
  }
}

#endif // CRUD_H