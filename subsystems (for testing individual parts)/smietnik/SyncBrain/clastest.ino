class paramC
{
    public:
   char * opis="opisc";
};

class C
{
    protected:
paramC pc;
public:

 C *next;

 void setNext(
     //C* v
     ) {
     //next=v;
   
     
     }
  C* getNext() { return next;}
  
 virtual  void logme() {

    Serial.write("no overiud");
    //Serial.write('c\n');
    Serial.write(pc.opis);
    Serial.write('\n');
} //=0;
};

class A:public C
{

public:   
A ()
{
  Serial.write("constrA ");  
  pc.opis="opiaa";
}
void logme() override
   {
       
       Serial.write("overridenA ");
   }

};

class B : public C
{
//const   char * opis="opibb";
public:  
B ()
{
  Serial.write("constrB ");  
}
 void logme() override
   {
       Serial.write("overrid b ");
       //Log("bbbb ");
   }

};