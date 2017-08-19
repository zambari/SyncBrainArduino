

#include <LinkedList.h>
Page *activePage;

LinkedList<Page *> *pages = new LinkedList<Page *>();

void setUpPages()
{
  Page_Sys a = Page_Sys();
  pages->add(&a);
  D d = D();
  B b = B();
  C c = C();
  D d2 = D();
  B b2 = B();
  C c2 = C();
  pages->add(&c2);
  pages->add(&b);
  pages->add(&c);
  pages->add(&d);
  pages->add(&b2);
  pages->add(&c2);
  pages->add(&d2);

  pageCount=pages->size();
  activePage=pages->get(0);


  for (int i = 0; i <pageCount; i++)
  {
  pages->get(i)->populateSubPages();
  pages->get(i)->postLayout(i);
  }
}
