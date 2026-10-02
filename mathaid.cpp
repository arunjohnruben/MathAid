 //MathAid
 //R.ARUN JOHN
 # include <process.h>
 # include <iostream.h>
 # include <dos.h>
 # include <graphics.h>
 # include <stdlib.h>
 # include <stdio.h>
 # include <ctype.h>
 # include <conio.h>
 # include <math.h>
 # include <string.h>
//*****************************************************
 const int size=200;
 void intro();
 void graphics();
 void border();
//*****************************************************
 struct stack
 {
   long double num;
   char symbol;
   stack *next;
 };
//*****************************************************
 class MathAid
 {
   double z;
   long double e;
   char infix[size],infixcopy[size],postfix[2*size];
   stack *top;

   void help();
   void input();
   void solve();
   void differentiate();
   void itop();
   int  chkprec(char ch);
   char popi();
   char givetop();
   void pushi(char ch);
   void validate();
   long double ptov();
   void push(long double);
   long double pop();
   void plot();

   public : MathAid()
            {
              z =0;    //default value for x
              e=2.718282;
            }
            void mainmenu();
 }Feb04;
//*****************************************************
 void main()
 {
   intro();
   Feb04.mainmenu();
   exit(0);
 }
//*****************************************************
 void graphics()
 {
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "C:\\Math-Aid\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
     printf("Graphics error: %s\\n", grapherrormsg(errorcode));
     printf("Press any key to halt:");
     getch();
     exit(1);
   }
 }
//*****************************************************
 void border()
 {
   cleardevice();
   setcolor(11);                      //border
   rectangle(0,0,639,479);
   rectangle(2,2,637,477);
 }
//*****************************************************
 void intro()
 {
   graphics();
   border();
   delay(1250);
   settextjustify(CENTER_TEXT, TOP_TEXT);
   settextstyle(SIMPLEX_FONT, HORIZ_DIR,8);
   for(int s=0;s<=8;s++)
   {
     cleardevice();
     setcolor(11);                      //border
     rectangle(0,0,639,479);
     rectangle(2,2,637,477);
     settextstyle(SCRIPT_FONT, HORIZ_DIR,s);
     for(int g=0;g<=5;g++)
     {
       setcolor(9);
       outtextxy (315+g,120+g,"MATH AID");
     }
     delay(90);
   }
   setcolor(4);
   settextstyle(GOTHIC_FONT, HORIZ_DIR,2);
   outtextxy (310,420,"R.Arun John");
   delay(2000);
 }
//*****************************************************
 void MathAid :: mainmenu()
 {
   char choice;
   do
   {
     border();
     gotoxy(30,5);
     cout<<"MAIN MENU ";
     gotoxy(15,9);
     cout<<"You can choose to";
     gotoxy(15,11);
     cout<<"1. Graphically plot any mathematical function";
     gotoxy(15,13);
     cout<<"2. Evaluate any mathematical function(Scientific calculator)";
     gotoxy(15,15);
     cout<<"3. Numerically differentiate any mathematical function";
     gotoxy(15,17);
     cout<<"4. MathAid Help";
     gotoxy(15,19);
     cout<<"0. Exit the program";
     do
       choice=getch();
     while(!(choice=='1'||choice=='2'||choice=='3' ||choice=='4' ||choice=='0' ));

     switch(choice)
     {
     case '1' :plot();
               break;

    case '2' : solve();
	       break;

    case '3' : differentiate();
	       break;

    case '4' : help();
	       break;
   }
   }while(choice!='0');
   closegraph();
 }
//*****************************************************
 void MathAid :: help()
 {
   border();
   gotoxy(33,3);
   cout<<"MathAid Help";
   gotoxy(5,6);
   cout<<"The following are the recognised function and symbols in Mathaid :-";
   gotoxy(5,8);
   cout<<"sin( )   cos( )   tan( )   sec( )   cosec( )   cot( )";
   gotoxy(5,9);
   cout<<"asin( )  acos( )  atan( )  asec( )  acosec( )  acot( )";
   gotoxy(5,10);
   cout<<"sinh( )  cosh( )  tanh( )  sech( )  cosech( )  coth( )";
   gotoxy(5,11);
   cout<<"log( )   log10( )";
   gotoxy(5,13);
   cout<<"[ ] or gi( )  - greatest integer function";
   gotoxy(5,14);
   cout<<"mod( ) or | | - modulus or absolute value function";
   gotoxy(5,15);
   cout<<"{ }           - fractional value function";
   gotoxy(5,16);
   cout<<"+   -   *    /    ^";
   gotoxy(5,17);
   cout<<"x   pi   e   0    1    2    3    4    5    6    7    8    9";
   gotoxy(5,19);
   cout<<"Note: (1) Unary operators should be enclosed in brackets ";
   gotoxy(5,20);
   cout<<"          to prevent ambiguity.";
   gotoxy(5,21);
   cout<<"      eg. tan(-x)+sech(x+e^(-sin(x)))";
   gotoxy(5,23);
   cout<<"      (2) | | should be used carefully.";
   gotoxy(5,24);
   cout<<"      eg. |sin(|x|)|+|x|, sin(mod(x))+|x|, |(-e^x)| and not|sin|x||+|x||";
   gotoxy(5,26);
   cout<<"      (3) If a particular function does not work please check domain,";
   gotoxy(5,27);
   cout<<"          reduce interval in grapher and retry.";
   gotoxy(5,29);
   cout<<"      (4) No caps please.";
   getch();
 }
//*****************************************************
 void MathAid :: input()
 {
   border();
   gotoxy(20,10);
   cout<<"Please enter mathematical expression ";
   gotoxy(15,14);
   cin>>infix;
   strcpy(infixcopy,infix);
 }
//*****************************************************
 void MathAid :: validate()
 {
   int l=0, r=0,error=0;
   for (int i=0 ;infix[i]!='\0'; i++)
   {
     if ( infix[i]=='(' )
       l++;
     else if ( infix[i]==')' )
       r++;
     else if(infix[i]!='x'&&infix[i]!='X'&&(!(infix[i]=='p'&&infix[i+1]=='i'))&&infix[i]!='e'&&infix[i]!='s'&&infix[i]!='i'&&infix[i]!='n'&&infix[i]!='c'&&infix[i]!='o'&&infix[i]!='t'&&infix[i]!='a'&&infix[i]!='l'&&infix[i]!='g'&&infix[i]!='m'&&infix[i]!='d'&&infix[i]!='h'&&infix[i]!='+'&&infix[i]!='-'&&infix[i]!='*'&&infix[i]!='/'&&infix[i]!='^'&&infix[i]!='['&&infix[i]!=']'&&infix[i]!='{'&&infix[i]!='}'&&infix[i]!='|'&&infix[i]!='.'&&infix[i]!='0'&&infix[i]!='1'&&infix[i]!='2'&&infix[i]!='3'&&infix[i]!='4'&&infix[i]!='5'&&infix[i]!='6'&&infix[i]!='7'&&infix[i]!='8'&&infix[i]!='9')
       {
	 error=1;
	 break;
       }
   }
   if ( l!=r )
   {
     cout<<"\n\tUnbalanced braces\n\n\tPress any key to terminate application";
     getch();
     exit(1);
   }
   else if(error)
   {
    cout<<"\n\tInvalid symbol present - Please see MathAid Help\n\n\tPress any key to terminate application";
    getch();
    exit(1);
   }
 }
//*****************************************************
 void MathAid :: itop()
 {
   int stprec,inprec,j=0;
   char popped;
   strcpy(postfix," ");
   for( int i=0;infix[i]!='\0';i++)
   {
     if( infix[i]=='[')
     {
       pushi('V');
       infix[i]='(';
       --i;
     }
     else if( infix[i]=='{')
     {
       pushi('W');
       infix[i]='(';
       --i;
     }
     else if( infix[i]==']'||infix[i]=='}'||( infix[i]=='|'&&( (!infix[i+1]) ||infix[i+1]==')'||infix[i+1]==']'||infix[i+1]=='}'||infix[i+1]=='+'||infix[i+1]=='-'||infix[i+1]=='*'||infix[i+1]=='/'||infix[i+1]=='^'  ) )  )
     {
       infix[i]=')';
       --i;
     }
     else if( infix[i]=='|')
     {
       pushi('U');
       infix[i]='(';
       --i;
     }
     else if(infix[i]!='('  &&  infix[i]!=')' &&  infix[i]!='^' &&  infix[i]!='*'  &&  infix[i]!='/' &&  infix[i]!='+'  &&  infix[i]!='-' )
     {
       if(infix[i]=='s'&&infix[i+1]=='i'&&infix[i+2]=='n'&&(infix[i+3]=='('||infix[i+3]=='|'||infix[i+3]=='{'||infix[i+3]=='[') )
       {
         pushi('A');
         i+=2;
       }
       else if(infix[i]=='c'&&infix[i+1]=='o'&&infix[i+2]=='s'&&(infix[i+3]=='('||infix[i+3]=='|'||infix[i+3]=='{'||infix[i+3]=='['))
       {
         pushi('B');
         i+=2;
       }
       else if(infix[i]=='t'&&infix[i+1]=='a'&&infix[i+2]=='n'&&(infix[i+3]=='('||infix[i+3]=='|'||infix[i+3]=='{'||infix[i+3]=='['))
       {
         pushi('C');
         i+=2;
       }
       else if(infix[i]=='c'&&infix[i+1]=='o'&&infix[i+2]=='s'&&infix[i+3]=='e'&&infix[i+4]=='c'&&(infix[i+5]=='('||infix[i+5]=='|'||infix[i+5]=='{'||infix[i+5]=='['))
       {
         pushi('D');
         i+=4;
       }
       else if(infix[i]=='s'&&infix[i+1]=='e'&&infix[i+2]=='c'&&(infix[i+3]=='('||infix[i+3]=='|'||infix[i+3]=='{'||infix[i+3]=='['))
       {
         pushi('E');
         i+=2;
       }
       else if(infix[i]=='c'&&infix[i+1]=='o'&&infix[i+2]=='t'&&(infix[i+3]=='('||infix[i+3]=='|'||infix[i+3]=='{'||infix[i+3]=='[') )
       {
         pushi('F');
 	 i+=2;
       }
       else if(infix[i]=='a'&&infix[i+1]=='s'&&infix[i+2]=='i'&&infix[i+3]=='n'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='[') )
       {
         pushi('G');
         i+=3;
       }
       else if(infix[i]=='a'&&infix[i+1]=='c'&&infix[i+2]=='o'&&infix[i+3]=='s'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='['))
       {
         pushi('H');
         i+=3;
       }
       else if(infix[i]=='a'&&infix[i+1]=='t'&&infix[i+2]=='a'&&infix[i+3]=='n'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='['))
       {
         pushi('I');
         i+=3;
       }
       else if(infix[i]=='a'&&infix[i+1]=='c'&&infix[i+2]=='o'&&infix[i+3]=='s'&&infix[i+4]=='e'&&infix[i+5]=='c'&&(infix[i+6]=='('||infix[i+6]=='|'||infix[i+6]=='{'||infix[i+6]=='['))
       {
         pushi('J');
	 i+=5;
       }
       else if(infix[i]=='a'&&infix[i+1]=='s'&&infix[i+2]=='e'&&infix[i+3]=='c'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='['))
       {
         pushi('K');
         i+=3;
       }
       else if(infix[i]=='a'&&infix[i+1]=='c'&&infix[i+2]=='o'&&infix[i+3]=='t'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='[') )
       {
         pushi('L');
 	 i+=3;
       }
       else if(infix[i]=='s'&&infix[i+1]=='i'&&infix[i+2]=='n'&&infix[i+3]=='h'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='[') )
       {
         pushi('M');
         i+=3;
       }
       else if(infix[i]=='c'&&infix[i+1]=='o'&&infix[i+2]=='s'&&infix[i+3]=='h'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='['))
       {
         pushi('N');
         i+=3;
       }
       else if(infix[i]=='t'&&infix[i+1]=='a'&&infix[i+2]=='n'&&infix[i+3]=='h'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='[') )
       {
         pushi('O');
         i+=3;
       }
       else if(infix[i]=='c'&&infix[i+1]=='o'&&infix[i+2]=='s'&&infix[i+3]=='e'&&infix[i+4]=='c'&&infix[i+5]=='h'&&(infix[i+6]=='('||infix[i+6]=='|'||infix[i+6]=='{'||infix[i+6]=='['))
       {
         pushi('P');
	 i+=5;
       }
       else if(infix[i]=='s'&&infix[i+1]=='e'&&infix[i+2]=='c'&&infix[i+3]=='h'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='['))
       {
         pushi('Q');
         i+=3;
       }
       else if(infix[i]=='c'&&infix[i+1]=='o'&&infix[i+2]=='t'&&infix[i+3]=='h'&&(infix[i+4]=='('||infix[i+4]=='|'||infix[i+4]=='{'||infix[i+4]=='[') )
       {
         pushi('R');
 	 i+=3;
       }
       else if( infix[i]=='l'&&infix[i+1]=='o'&&infix[i+2]=='g'&&(infix[i+3]=='('||infix[i+3]=='|'||infix[i+3]=='{'||infix[i+3]=='['))
       {
	 pushi('S');
	 i+=2;
       }
       else if( infix[i]=='l'&&infix[i+1]=='o'&&infix[i+2]=='g'&&infix[i+3]=='1'&&infix[i+4]=='0'&&(infix[i+5]=='('||infix[i+5]=='|'||infix[i+5]=='{'||infix[i+5]=='['))
       {
	 pushi('T');
	 i+=4;
       }

       else if(infix[i]=='m'&&infix[i+1]=='o'&&infix[i+2]=='d'&&(infix[i+3]=='('||infix[i+3]=='|'||infix[i+3]=='{'||infix[i+3]=='['))
       {
         pushi('U');
         i+=2;
       }
       else if( infix[i]=='g'&&infix[i+1]=='i'&&(infix[i+2]=='('||infix[i+2]=='|'||infix[i+2]=='{'||infix[i+2]=='['))
       {
	 pushi('V');
         i+=1;
       }
       else if(   (infix[i]>=48&&infix[i]<=57)||infix[i]=='e' ||(infix[i]=='p'&&infix[i+1]=='i')||infix[i]=='x'||infix[i]=='X' || infix[i]=='.' )
       {
	 while(   (infix[i]>=48&&infix[i]<=57)||infix[i]=='e' ||infix[i]=='p'||infix[i]=='i'||infix[i]=='x'||infix[i]=='X' || infix[i]=='.' )
	   postfix[j++]=infix[i++];
	 --i;
	 postfix[j++]=' ';
       }
       else
       {
         cout<<"\n\tInvalid expression - Please see MathAid Help\n\n\tPress any key to terminate application";
         getch();
         exit(1);
       }
     }
     else if (infix[i]=='(')
     {
//unary operator check
       if( infix[i+1]=='-' || infix[i+1]=='+' )
       {
	 postfix[j++]='0';
	 postfix[j++]=' ';
       }
       pushi('(');
     }
     else if (infix[i]==')')
     {
       while((popped=popi())!='(')
       {
	 postfix[j++]=popped;
	 postfix[j++]=' ';
       }
     }
//now infix[i] is a operator
     else
     {
       inprec=chkprec(infix[i]);
       stprec=chkprec(givetop());
       while(stprec>=inprec)
       {
	 if(givetop()=='#')
	   break;
	 postfix[j++]=popi();
	 postfix[j++]=' ';
	 stprec=chkprec(givetop());
       }
       pushi(infix[i]);
     }
   }
   while((popped=popi())!='#')
   {
     postfix[j++]=popped;
     postfix[j++]=' ';
   }
   postfix[j]='\0';
 }
//*****************************************************
 int MathAid :: chkprec(char ch)
 {
   switch(ch)
   {
     case'A':case'B':case'C':case'D':case'E':case'F':case'G':case'H':case'I':
     case'J':case'K':case'L':case'M':case'N':case'O':case'P':case'Q':case'R':case'S':case'T':
     case'U':case'V':case'W':case'X':case'Y':case'Z':
             return 4;
     case'^':return 3;
     case'/':case'*':
             return 2;
     case'+':case'-':
             return 1;
     default:return 0;
   }
 }
//*****************************************************
 char MathAid :: popi()
 {
   char ret;
   stack * del=top;
   if(top)
   {
     ret= top->symbol;
     top=top->next;
     delete del;
     return ret;
   }
   else
   return '#';
 }
//*****************************************************
 char MathAid :: givetop()
 {
   if (top)
     return(top->symbol);
   else
     return('#');
 }
//*****************************************************
 void MathAid :: pushi( char ch)
 {
  stack *p=new stack;
   if (p)
   {
     p->symbol=ch;
     p->next=top;
     top=p;
   }
   else
   {
     cout<<"\n\n\tMemory not enough\n"
     <<"\tPress any key to terminate application";
     getch();
     exit(1);
   }
 }
//*****************************************************
 long double MathAid :: ptov()
 {
   int i=0,f=0;
   long double s1,s2,dummy;
   char temp_opnd[size];
   do
   {
     if(    ( (postfix[i]>=48 && postfix[i]<=57 ) ||(postfix[i]=='-' && i==0) )   ||  postfix[i]=='.' )
     {
       while(postfix[i]!=' ')
       {
	 temp_opnd[f]=postfix[i];
	 f++;i++;
       }
       temp_opnd[f]='\0';
       --i;
       long double n=atof(temp_opnd);
       f=0;
       push(n);
     }
     if(postfix[i]=='x'||postfix[i]=='X')
       push(z);
     if(postfix[i]=='e')
       push(e);
     if(postfix[i]=='p'&&postfix[i+1]=='i')
       push(M_PI);
     if(postfix[i]=='*')
       push(pop()*pop());
     if(postfix[i]=='+')
       push(pop()+pop());
     if(postfix[i]=='-')
     {
       push(-pop()+pop());
     }
     if(postfix[i]=='/')
     {
       push(  (1/pop())*pop() );
     }
     if(postfix[i]=='^')
     {
       s1=pop();
       s2=pop();
       push(powl(s2,s1));
     }
     if(postfix[i]=='A')                //s for sin  A
       push(sinl(pop()));
     if(postfix[i]=='B')                //c for cos  B
       push(cosl(pop()) );
     if(postfix[i]=='C')                // t for tan C
       push(tanl(pop()));
     if(postfix[i]=='D')                //s for cosec D
       push(1/sinl( pop()  )  );
     if(postfix[i]=='E')                //s for sec E
       push(1/cosl(pop()  ));
     if(postfix[i]=='F')                //s for cot F
       push(1/tanl( pop()   )  );
     if(postfix[i]=='G')                //s for sin inverse G
       push(asinl( pop()   )  );
     if(postfix[i]=='H')                //s for cos inverse H
       push(acosl( pop()   )  );
     if(postfix[i]=='I')                //s for tan inverse I
       push(atanl( pop()   )  );
     if(postfix[i]=='J')                //s for cosec inverse J
       push(asinl( 1/pop()   )  );
     if(postfix[i]=='K')                //s for sec inverse K
       push(acosl( 1/pop()   )  );
     if(postfix[i]=='L')                //s for cot inverse L
       push(atanl( 1/pop()   )  );
     if(postfix[i]=='M')                //s for sin hyperbolic M
     {
      s1=pop() ;
      s2=expl(s1);
      s1=expl(-s1);
      push((s2-s1)/2);
     }
     if(postfix[i]=='N')                //c for cos hyperbolic N
     {
      s1=pop() ;
      s2=expl(s1);
      s1=expl(-s1);
      push( (s1+s2)/2 );
     }
     if(postfix[i]=='O')                // t for tan hyperbolic O
     {
      s1=pop() ;
      s2=expl(s1);
      s1=expl(-s1);
      push( (s2-s1)/(s1+s2) );
     }
     if(postfix[i]=='P')                //s for cosec hyperbolic P
     {
      s1=pop() ;
      s2=expl(s1);
      s1=expl(-s1);
      push( 2/(s2-s1) );
     }
     if(postfix[i]=='Q')                //s for sec hyperbolic Q
     {
      s1=pop() ;
      s2=expl(s1);
      s1=expl(-s1);
      push( 2/(s1+s2) );
     }
     if(postfix[i]=='R')                //s for cot hyperbolic R
     {
      s1=pop() ;
      s2=expl(s1);
      s1=expl(-s1);
      push( (s1+s2)/(s2-s1) );
     }
     if(postfix[i]=='S')                //l for natural log S
       push(logl(pop())  );
     if(postfix[i]=='T')                //l for log to the base 10 T
       push(log10l(pop())  );
     if(postfix[i]=='U')                //m for modulus U
       push(fabsl(pop() )  );
     if(postfix[i]=='V')                //g for greatest integer V
       push(floorl( pop() )  );
     if(postfix[i]=='W')                //f for fractional part W
       push(modfl( pop(),&dummy )  );
   }while(postfix[++i]);
   long double rt=pop();
   return rt;
 }
//*****************************************************
 void MathAid :: push(long double l)
 {
   stack *p=new stack;
   if(p)
   {
   p->num=l;
   p->next=top;
   top=p;
   }
   else
   {
     cout<<"\n\n\tMemory not enough\n"
     <<"\tPress any key to terminate application";
     getch();
     exit(1);
   }
 }
//*****************************************************
 long double MathAid :: pop()
 {
   long double ret;
   stack *del;
   ret=top->num;
   del=top;
   top=top->next;
   delete del;
   return ret;
 }
//*****************************************************
  void MathAid :: plot()
 {
   input();
   validate();
   itop();
   border();
   float s=1.0,rts=1.0;
   char choice='r';
   long double x1,x2,ox1,ox2,y,increment=0.0001;
   int xp=0,yp=0;
   gotoxy(15,8);
   cout<<"Please enter lower limit  and upper limit for x ";
   gotoxy(15,10);
   cout<<"minimum x  =  ";cin>>ox1;
   x1=ox1;
   gotoxy(15,12);
   cout<<"maximum x  =  ";cin>>ox2;
   x2=ox2;
   delay(100);
   do
   {
   cleardevice();
   setbkcolor(0);
//  *********axis settings*************
   setcolor(7);
   setlinestyle(SOLID_LINE ,SOLID_LINE ,NORM_WIDTH) ;
// y-axis
   line(320,0,320,480);
   line(320,0,320-3,5);
   line(320,0,320+3,5);
   line(320,480,317,480-5);
   line(320,480,323,480-5);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(SMALL_FONT, HORIZ_DIR, 4);
   outtextxy (296,6,"y-axis");
// x-axis
   line(0,240,640,240);
   line(0,240,5,240+3);
   line(0,240,5,240-3);
   line(640,240,640-5,240+3);
   line(640,240,640-5,240-3);
   settextjustify(RIGHT_TEXT, TOP_TEXT);
   settextstyle(SMALL_FONT, HORIZ_DIR, 4);
   outtextxy (636,240,"x-axis");
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(SMALL_FONT, HORIZ_DIR, 4);
   outtextxy (305,245,"(0,0)");
// border
   rectangle(0,0,639,479);
   if( (s*24*ox1+320)<-1)
     x1=-320/(s*24);
   if( (s*24*ox2+320)>640+1)
     x2=320/(s*24);
//*****THE PLOTTER*******
   for(z=x1;z<=x2;z+=increment)
   {
     xp=s*24*z+320;
     y=s*24*(ptov());
     yp=240-y;
     putpixel(xp,yp,9);
   }
   getch();
   border();
   gotoxy(35,8);
   cout<<"Press";
   gotoxy(10,11);
   cout<<"Z - zoom_in ,zoom_out";
   gotoxy(10,12);
   cout<<"R - repeat";
   gotoxy(10,13);
   cout<<"E - exit";
   do
     choice=getche();
   while(choice!='e' &&  choice!='z' &&  choice!='r'  );
     if(tolower(choice)=='z')
     {
       gotoxy(10,15);
       cout<<"Enter scale factor   ";cin>>rts;
       s*=rts;
       increment=0.0001;
       if(s>1)
         increment=0.0001/s;
       x1=ox1;
       x2=ox2;
     }
 }while(tolower(choice)!='e');
 }
//*****************************************************
 void MathAid :: solve()
 {
   input();
   validate();
   itop();
   border();
   gotoxy(15,10);
   cout<<infixcopy<<" =  "<<ptov();
   getch();
 }
//*****************************************************
 void MathAid :: differentiate()
 {
   long double y1=1,y2=1,increment=1e-10,d;
   char a[size];
   input();
   validate();
   border();
   gotoxy(20,10);
   cout<<"Please specify value of x  :  ";cin>>infix;
   validate();
   itop();
   z=ptov();
   strcpy(infix,infixcopy);
   itop();
   y1=(ptov());
   z+=increment;
   y2=(ptov());
   d=((y2-y1)/increment);
   gcvt(d,5,a);
   border();
   gotoxy(15,8);
   cout<<"Co-efficient of differentiation of "<<infixcopy<<" is";
   gotoxy(15 ,10);
   cout<<a;
   getch();
 }
//*****************************************************
/*
COMMENTS

Built by R. ARUN JOHN
FOR AISSCE 2004
COMPUTER SCIENCE PROJECT
CLASS 12
NATIONAL PUBLIC SCHOOL
BANGALORE
INDIA
*/
//*****************************************************