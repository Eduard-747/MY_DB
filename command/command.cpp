#include "command.h"

#include <vector>
#include <string>
#include <iostream>

size_t myl::mhash::operator()(const myl::DataBase& o) const
{
  return std::hash<std::string>{}(o.get_DataBase_name());
}

std::string myl::Command::_creat(const std::vector<std::string>& tokens)
{
  try
  {
    crud.creat_DB(tokens.at(1));
  }
  catch(const std::exception& e)
  {
    
    return "eeee chelav ay axper\n" ;
  }

  return "lava lava\n";
}

std::string myl::Command::_creat_table(const std::vector<std::string>& tokens)
{
  try
  {
    crud.set_table(tokens.at(1),std::vector<std::string>(tokens.begin() + 2, tokens.end()));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }

  return "lava lava\n";
}

std::string myl::Command::_creat_DB_and_tables(const std::vector<std::string>& tokens)
{
  try
  {
    crud.creat_DB(tokens.at(1), std::vector<std::string>(tokens.begin() + 2, tokens.end()));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }

  return "lava lava\n";
}

std::string myl::Command::_push_info(const std::vector<std::string>& tokens)
{
  try
  {
    crud.push_info(tokens.at(1), tokens.at(2), tokens.at(3));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }

  return "lava lava\n";
}

std::string myl::Command::_read(const std::vector<std::string>& tokens) 
{
  try
  {
    return crud.get_DB(tokens.at(1));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }
}

std::string myl::Command::_read_table(const std::vector<std::string>& tokens)
{
  try
  {
    return crud.get_table(tokens.at(1), tokens.at(2));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }
}

std::string myl::Command::_read_info(const std::vector<std::string>& tokens)
{
  try
  {
    return crud.get_info(tokens.at(1),tokens.at(2), std::stoi(tokens.at(3)));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }

}

std::string myl::Command::_update(const std::vector<std::string>& tokens)
{
  try
  {
    crud.change_info(tokens.at(1), tokens.at(2), std::stoi(tokens.at(3)), tokens.at(4));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }

  return "lava lava\n";
}

std::string myl::Command::_delete(const std::vector<std::string>& tokens)
{
  try
  {
    crud.delete_DB(tokens.at(1));
    system(("rm ./DataBaseTxt/" + tokens.at(1)).c_str());
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }

  return "lava lava\n";
}

std::string myl::Command::_delete_table(const std::vector<std::string>& tokens)
{
  try
  {
    crud.delete_table(tokens.at(1), tokens.at(2));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }

  return "lava lava\n";
}

std::string myl::Command::_delete_info(const std::vector<std::string>& tokens) 
{
  try
  {
    crud.delete_info(tokens.at(1), tokens.at(2), std::stoi(tokens.at(3)));
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper\n" ;
  }

  return "lava lava\n";
}

std::string myl::Command::_disconnect(const std::vector<std::string>& tokens)
{
  return "thank you\n";
}

myl::Command::Command()
{
  com_coll["creat"] = &Command::_creat;
  com_coll["creat_DB_tables"] = &Command::_creat_DB_and_tables;
  com_coll["creat_table"] = &Command::_creat_table;
  com_coll["creat_info"] = &Command::_push_info;
  com_coll["read"] = &Command::_read;
  com_coll["read_table"] = &Command::_read_table;
  com_coll["read_info"] = &Command::_read_info;
  com_coll["update"] = &Command::_update;
  com_coll["delete"] = &Command::_delete;
  com_coll["delete_table"] = &Command::_delete_table;
  com_coll["delete_info"] = &Command::_delete_info;
  com_coll["disconnect"] = &Command::_disconnect;
}

std::string myl::Command::coll_command(const std::vector<std::string>& tokens)
{
  try
  {
    return (this->*com_coll.at(tokens[0]))(tokens);
  }
  catch(const std::exception& e)
  {
    return "eeee chelav ay axper tenc hraman chka\n" ;
  }
}