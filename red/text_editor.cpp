#include <iostream>
#include <string>
#include <string_view>
#include "test_runner.h"
#include <list>
using namespace std;

class Editor {
 public:
  Editor() {
    s = "";
    buffer = "";
    size = 0;
    index = 0;
    V = text.begin();
  }
  void Left() {
    if (index > 0) {
        index--;
        V--;
    }
  }
  void Right() {
    if (index < size) {
        index ++;
        V++;
    }
  }
  void Insert(char token) {
   // string new_string(s.begin(),s.begin() + index);
   // string c(1,token);
   // new_string += c;
   // new_string += string(s.begin()+index, s.end());
  //  s = new_string;
   // text.insert( next(text.begin(),index), token);
   V = text.insert(V, token);
    index++;
    V++;
    size++;

  }
  void Cut(size_t tokens = 1) {
    list<char> New_buf;

    tokens = min(tokens,size - index);
    if (tokens == 0) {
        Buf = New_buf;
        return;
    }

    /*
    buffer = s.substr(index, tokens);
    string new_string(s.begin(),s.begin() + index);
    new_string += string(s.begin() + index + tokens, s.end());
    s = new_string;*/
    int i = 0;
    while (i < tokens) {
       // New_buf.push_back(*(next(text.begin(),index)));
        //text.erase( next(text.begin(),index));
        New_buf.push_back(*V);
        V = text.erase(V);
        ++i;
    }
    //for (auto &j : Buf)
    Buf = New_buf;
    size -= tokens;
  //  tokens = min(tokens,size - index);


  }
  void Copy(size_t tokens = 1) {
    tokens = min(tokens,size - index);
    //buffer = s.substr(index, tokens);
    list<char> New_buf;
    int i = 0;
    while (i < tokens) {
        //New_buf.push_back( *(next(text.begin(), i + index)));
        New_buf.push_back( *(next(V, i)));
        ++i;
    }
    Buf = New_buf;
  }
  void Paste() {
      int i = 0;
     /* while (i < Buf.size()) {
        text.insert( next(text.begin() ,index + i),* next(Buf.begin(),i)) ;
        ++i;
      } */
    //text.insert(next(text.begin() ,index + i),Buf.begin(), Buf.end());
    V = text.insert(next(V,i),Buf.begin(), Buf.end());
    V = next(V,Buf.size());
    size += Buf.size();
    index += Buf.size();
/*
    string  new_string (s.begin(), s.begin() + index);
    new_string += buffer;
    new_string += string(s.begin() + index, s.end());
    size += buffer.size();
    index += buffer.size();
    s = new_string;

  if (index == size) {
    s += buffer;
  } else {
        string_view str = s;
        string_view pre = str.substr(0,index);
        string_view suf = str.substr(index,size - index);
        string New_string = string(size + buffer.size(), 'a');
        int i = 0;
        while (i < index) {
            New_string[i] = pre[i];
        }
        while (i - index < buffer.size()) {
            New_string[i] = buffer[i];
        }
        while (i < size + buffer.size()) {
            New_string[i] = suf[i - index - buffer.size()];
        }
        s = New_string;

  }

     size += buffer.size();
     index += buffer.size(); */

  }

  string GetText() const {
    return string(text.begin(), text.end());
  }
  void GetIndex() {
    cout << " " << " index is " << index << endl;
  }

 private:
    list<char> text;
    list<char> Buf;
    list<char> :: iterator V;
    int index = 0;
    string buffer = "";
    string_view result;
    string s = "";
    size_t size = 0;
   // deque <char> DEQ;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    //cout << " TYPE TEXT " << endl;
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    editor.GetIndex();
    cout << editor.GetText() << endl;
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.GetIndex();
   // cout << editor.GetText() << endl;
    editor.Cut(first_part_len);
    editor.GetIndex();
    cout << "TUT";
    cout << editor.GetText() << endl;
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    editor.GetIndex();
    TypeText(editor, ", ");
    editor.GetIndex();
    cout << editor.GetText() << endl ;
    editor.Paste();
    editor.GetIndex();
    cout << editor.GetText() << endl ;
    editor.Left();
    editor.Left();
    editor.Cut(3);
    cout << editor.GetText()<< endl << " after cut"  << endl;
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  cout << editor.GetText() << endl;

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
 cout << " all is ok "  << endl;
  return 0;
}
/*

int main() {
    std::string s {"hello"};
    std::string_view ss(s);
    cout << s << " " << ss;
    s += "worldworldworldworldworldworldworldworldworldworldworldworldworldworldworldworldPPPPPP";
    cout << endl << s << " " << ss;
    return 0;

} */
