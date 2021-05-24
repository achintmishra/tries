#include <iostream>
#include<string>
#include<vector>
using namespace std;

class trienode
{
  public:
  char data;
  trienode **children;
  bool isterminal;
  trienode(char data)
  {
    this->data=data;
    children = new trienode*[26];
    for(int i=0;i<26;i++)
    {
      children[i]=NULL;
    }
    isterminal=false;
  }
};
class trie
{
  trienode *root;
  public:
  trie()
  {
    root = new trienode('\0');
  }
  void insertword(trienode *root,string word)
  {
    if(word.size()==0)
    {
      root->isterminal=true;
      return;
    }
    int index = word[0]-'a';
    trienode *child;
    if(root->children[index]!=NULL)
    {
      child = root->children[index];
    }
    else
    {
      child = new trienode(word[0]);
      root->children[index]=child;
    }
    insertword(child,word.substr(1));
  }
  void insert(string word)
  {
    insertword(root,word);
  }
  bool searchword(trienode*root,string word)
  {
    if(word.size()==0)
    {
      return root->isterminal;
    }
    trienode*child;
    int index=word[0]-'a';
    if(root->children[index]!=NULL)
    {
      child=root->children[index];
    }
    else
    {
      return false;
    }
    return searchword(child,word.substr(1));
  }
  bool search(string word)
  {
    return searchword(root,word);
  } 
  void removeword(trienode*root,string word)
  {
    if(word.size()==0)
    {
      root->isterminal=false;
      return;
    }
    trienode*child;
    int index=word[0]-'a';
    if(root->children[index]!=NULL)
    {
      child=root->children[index];
    }
    else
    {
      return;
    }
    removeword(child,word.substr(1));
    if(child->isterminal==false)
    {
      for(int i=0;i<26;i++)
      {
        if(child->children[i]!=NULL)
        {
          return;
        }
      }
      delete child;
      root->children[index]=NULL;
    }
  }
  void remove(string word)
  {
    removeword(root,word);
  }
};
int main() 
{
  trie t;
  t.insert("and");
  t.insert("are");
  t.insert("dot");
  cout<<t.search("and")<<endl;
  t.remove("and");
  cout<<t.search("and")<<endl;
} 