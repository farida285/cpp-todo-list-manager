#include <iostream>
#include <limits>
#include <string>
using namespace std ;
const unsigned short MAX_TASKS = 100;
enum enOperation {
    Nothing,Add,ViewAll,ViewPending,ViewCompleted,ViewTaskDetails,Edit,
    MarkDone,MarkPending,DeleteTask,DeleteAllTasks,Exit
} ;
enum enPriority {High=1,Medium=2,Low=3};
enum enStatus {Pending,Done};
enum enEdit {Title=1,Description=2,Priority=3,Cancel=4};
struct stTask
{
    unsigned short taskNumber ;
    string title ;
    string description ;
    enPriority priority ;
    enStatus status ;
};
struct stToDoList {
    stTask tasks [MAX_TASKS];
    unsigned short numberOfTasks=0 , numberOfDoneTasks=0 ,numberOfPendingTasks=0;
    enOperation currentOperation=enOperation::Nothing ;
};
unsigned short PositiveShortNumberInRange (const string &message , unsigned short from , unsigned short to ){
    int number ;
    cout<<message<<endl ;
    bool invalidinput ;
    do{
        invalidinput =0 ;
        if (!(cin >> number))  
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            invalidinput =1;
        }else if(number<from||number>to){
            cout<<"Unavailable numbers!!\n" ;
            cout<<"Enter number in range from "<<from<<" to "<<to<<".\n";
            invalidinput =1;
        }
    }while(invalidinput);
    return (unsigned short)number ;
}
unsigned short GetTaskNumber (const string &message ,unsigned short numberOfTasks ){
    int number ;
    cout<<message<<endl ;
    bool invalidinput ;
    do{
        invalidinput =0 ;
        if (!(cin >> number))  
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            invalidinput =1;
        }else if(number<1||number>numberOfTasks){
            cout<<"Invalid task number!\n" ;
            cout<<"You have "<<numberOfTasks<<" tasks.\n";
            cout<<"Enter the number:\n";
            invalidinput =1;
        }
    }while(invalidinput);
    return (unsigned short)number ;
}
string GetStringInSize (const string &message,unsigned short from,unsigned short to){
    string text ;
    unsigned size ;
    cout << message<<endl;
    do{
        getline(cin>>ws,text) ;
        size=text.size() ;
        if(size>to||size<from){
            cout <<"Enter text in range from "<<from<<" to "<<to<<" characters:\n";
        }
    }while(size>to||size<from) ;
    return text ;
}
bool YesOrNo (const string &message){
    string Answer ;
    cout<<message<<endl;
    do{
        cin>>Answer ;

        if( !(Answer=="Yes"||Answer=="YES"||Answer=="yes"||Answer=="y"||Answer=="Y"||
            Answer=="No"||Answer=="NO"||Answer=="N"||Answer=="n"||Answer=="no"))
            {
            cout<<"Please Enter yes or no : \n" ;
            }
    }while(!(Answer=="Yes"||Answer=="YES"||Answer=="yes"||Answer=="y"||Answer=="Y"||
            Answer=="No"||Answer=="NO"||Answer=="N"||Answer=="n"||Answer=="no"));
    if(Answer=="Yes"||Answer=="YES"||Answer=="yes"||Answer=="y"||Answer=="Y"){
        return 1 ;
    }else{
        return 0 ;
    }
    

}
string Tabs( short number){
    string tabs ="" ;
    if (number>0){
        for(unsigned i =1 ;i<=number;i++){
        tabs=tabs+"\t";
    }

    }
    
    return tabs ;
}
void PrintMainMenu (const stToDoList &list){
    cout<<"================================================================\n";
    cout<<"                       TO-DO LIST MANAGER\n";
    cout<<"================================================================\n";
    cout<<endl;
    cout<<"Total Tasks     : "<<list.numberOfTasks<<"\n";
    cout<<"Pending Tasks   : "<<list.numberOfPendingTasks<<"\n";
    cout<<"Completed Tasks : "<<list.numberOfDoneTasks<<"\n";
    cout<<endl;
    cout<<"----------------------------------------------------------------\n";
    cout<<"1.  Add New Task\n";
    cout<<"2.  View All Tasks\n";
    cout<<"3.  View Pending Tasks\n";
    cout<<"4.  View Completed Tasks\n";
    cout<<"5.  View Task Details\n";
    cout<<"6.  Edit Task\n";
    cout<<"7.  Mark Task as Done\n";
    cout<<"8.  Mark Task as Pending\n";
    cout<<"9.  Delete Task\n";
    cout<<"10. Delete All Tasks\n";
    cout<<"11. Exit\n";
    cout<<"----------------------------------------------------------------\n";


}
void ConfirmExit(enOperation &operation){
   if(YesOrNo("Are you sure you want to exit? (Yes/No) ?")){
         cout<<"\nThank you for using To-Do List Manager.\nGoodbye!\n";
     }else{
         operation=enOperation::Nothing ;
        }
}
stTask AddTaskFromUser (){
    stTask task ;
    cout<<"===================== ADD NEW TASK =====================\n";
    cout<<endl;
    task.title=GetStringInSize("Enter task title :",3,50);
    cout<<endl ;
    task.description=GetStringInSize("Enter task description :",1,200);
    cout<<endl ;
    task.priority=(enPriority)PositiveShortNumberInRange("Choose task priority :\n[1]High\n[2]Medium\n[3]Low\nEnter choice:",1,3);
    task.status=enStatus::Pending ;
    return task ;

}
void AddTaskInList (stToDoList &list){
   if(list.numberOfTasks==MAX_TASKS){
     cout<<"Task list is full (maximum tasks is "<<MAX_TASKS<<"). Cannot add more tasks.\n";
   }else{
    list.tasks[list.numberOfTasks]=AddTaskFromUser();
    list.tasks[list.numberOfTasks].taskNumber=list.numberOfTasks+1;
    list.numberOfTasks++;
    list.numberOfPendingTasks++;
    cout<<"\n+++ Task added successfully. +++\n";
   }
   
}
string PriorityString (enPriority priority){
    string arr[3]={"High","Medium","Low"};
    return arr[(unsigned short)priority-1] ;
}
string StatusString (enStatus status){
    string arr[2]={"Pending","Done"};
    return arr[(unsigned short)status] ;
}
void PrintOneTaskInView(const stTask &task){
    cout<<task.taskNumber<<Tabs(1)<<StatusString(task.status)<<Tabs(2)<<PriorityString(task.priority)<<Tabs(2)<<task.title<<endl ;
}
void ViewAllList (const stToDoList &list){
    if(list.numberOfTasks>0){
    cout<<"===================== VIEW ALL TASKS =====================\n";
    cout<<endl ;
    cout<<"Number"<<Tabs(1)<<"Status"<<Tabs(2)<<"Priority"<<Tabs(1)<<"Title\n";
    cout<<"----------------------------------------------------------\n";
    for(unsigned short i=0;i<list.numberOfTasks;i++){
        PrintOneTaskInView(list.tasks[i]) ;
    }
    }else{
        cout<<"No tasks found.\n";
    }
  
}
void ViewPendingTasks(const stToDoList &list){
    if(list.numberOfTasks>0){
        unsigned short  foundTaskCount =0 ;
        for(unsigned short i=0 ;i<list.numberOfTasks;i++){
            if(list.tasks[i].status==enStatus::Pending){
             foundTaskCount++ ;
                if(foundTaskCount==1){
                    cout<<"===================== VIEW PENDING TASKS =====================\n";
                    cout<<endl ;
                    cout<<"Number"<<Tabs(1)<<"Status"<<Tabs(2)<<"Priority"<<Tabs(1)<<"Title\n";
                    cout<<"--------------------------------------------------------------\n";
                }
             PrintOneTaskInView(list.tasks[i]) ;
            }

        }
        if(foundTaskCount==0){
             cout<<"No Pending tasks found.\n";
        }
    }else{
        cout<<"You do not have any tasks.\n";
    }
}
void ViewCompletedTasks(const stToDoList &list){
    if(list.numberOfTasks>0){
        unsigned short  foundTaskCount =0 ;
        for(unsigned short i=0 ;i<list.numberOfTasks;i++){
            if(list.tasks[i].status==enStatus::Done){
              foundTaskCount++ ;
                if( foundTaskCount==1){
                    cout<<"===================== VIEW COMPLETED TASKS =====================\n";
                    cout<<endl ;
                    cout<<"Number"<<Tabs(1)<<"Status"<<Tabs(2)<<"Priority"<<Tabs(1)<<"Title\n";
                    cout<<"--------------------------------------------------------------\n";
                }
             PrintOneTaskInView(list.tasks[i]) ;

            }

        }
        if( foundTaskCount==0){
             cout<<"No completed tasks found.\n";
        }
    }else{
        cout<<"You do not have any tasks.\n";
    }
}
void PrintOneTaskInDetails(const stTask &task){
    cout<<"Task Number      : "<<task.taskNumber<<endl;
    cout<<"Task Title       : "<<task.title<<endl;
    cout<<"Task Priority    : "<<PriorityString(task.priority)<<endl;
    cout<<"Task Status      : "<<StatusString(task.status)<<endl;
    cout<<"Task Description : "<<task.description<<endl;
}
void ViewTask (const stToDoList &list){
     if(list.numberOfTasks>0){
      cout<<"===================== VIEW TASK =====================\n";
      unsigned short taskNumberToView=GetTaskNumber("Enter task number to view:",list.numberOfTasks);
      cout<<endl;
      PrintOneTaskInDetails(list.tasks[taskNumberToView-1]);
     }else{
        cout<<"You do not have any tasks.\n";
     }
      
}
void MarkAsCompleted(stToDoList &list){
     if(list.numberOfTasks>0){
      cout<<"===================== MARK TASK =====================\n";
      unsigned short taskNumberToMark=GetTaskNumber("Enter task number to mark:",list.numberOfTasks);
      cout<<endl;
      if(list.tasks[taskNumberToMark-1].status==enStatus::Done){
        cout<<"This task is already completed.\n";
      }else{
        list.tasks[taskNumberToMark-1].status=enStatus::Done ;
        list.numberOfDoneTasks++;
        list.numberOfPendingTasks--;
        cout<<"+++ Task marked as completed successfully. +++\n";
      }
     }else{
        cout<<"You do not have tasks to mark!\n";
     }
}
void MarkAsPending(stToDoList &list){  
    if(list.numberOfTasks>0){
      cout<<"===================== MARK TASK =====================\n";
      unsigned short taskNumberToMark=GetTaskNumber("Enter task number to mark:",list.numberOfTasks);
      cout<<endl;
      if(list.tasks[taskNumberToMark-1].status==enStatus::Pending){
        cout<<"This task is already pending.\n";
      }else{
        list.tasks[taskNumberToMark-1].status=enStatus::Pending ;
        list.numberOfDoneTasks--;
        list.numberOfPendingTasks++;
        cout<<"+++ Task marked as pending successfully. +++\n";
      }
     }else{
        cout<<"You do not have tasks to mark!\n";
     }
}
void DeleteTaskAndShiftLeft(stToDoList &list,unsigned short taskNumberToDelete){
    if(list.tasks[taskNumberToDelete-1].status==enStatus::Done){
        list.numberOfDoneTasks--;
    }else{
        list.numberOfPendingTasks--;
    }
   
    for(unsigned i = taskNumberToDelete;i<list.numberOfTasks;i++){
        list.tasks[i-1]=list.tasks[i] ;
        list.tasks[i-1].taskNumber=i;
    }
    list.numberOfTasks--;
        
}
void DeleteOneTask(stToDoList &list){
     if(list.numberOfTasks>0){
      cout<<"===================== DELETE TASK =====================\n";
      unsigned short taskNumberToDelete=GetTaskNumber("Enter task number to delete:",list.numberOfTasks);
      cout<<endl;
      PrintOneTaskInDetails(list.tasks[taskNumberToDelete-1]);
      if(YesOrNo("Are you sure you want to delete this task? (Yes/No)")){
        DeleteTaskAndShiftLeft(list,taskNumberToDelete);
        cout<<"+++ Task deleted successfully. +++\n";
      }else{
        cout<<"+++ Delete operation canceled. +++\n";
      }

     }else{
        cout<<"You do not have tasks to delete!\n";
     }
}
void DeleteAll(stToDoList &list){
if(list.numberOfTasks>0){
  if(YesOrNo("Are you sure you want to delete all tasks? (Yes/No) ?")){
    list.numberOfTasks=0;
    list.numberOfDoneTasks=0;
    list.numberOfPendingTasks=0; 
    cout<<"+++ Tasks deleted successfully. +++\n";
     }else{
         cout<<"+++ Delete all operation canceled. +++\n";
        }
   
}else{
    cout<<"You do not have any tasks.\n";
}
}
void EditOneParameter(enEdit option,stTask &task){
    switch (option)
    {
    case enEdit::Title:
        task.title=GetStringInSize("Enter task title :",3,50);
        break;
    case enEdit::Description:
        task.description=GetStringInSize("Enter task description :",1,200);
        break;
    case enEdit::Priority:
        task.priority=(enPriority)PositiveShortNumberInRange("Choose task priority :\n[1]High\n[2]Medium\n[3]Low\nEnter choice:",1,3);
        break ;
    case enEdit::Cancel:
      cout<<"+++ Edit operation canceled. +++\n";
      break ; 
    default:
        break;
    }

}
void EditTask(stToDoList &list){
     if(list.numberOfTasks>0){
      enEdit option ;
      cout<<"===================== EDIT TASK =====================\n";
      unsigned short taskNumberToEdit=GetTaskNumber("Enter task number to edit:",list.numberOfTasks);
      cout<<endl;
      PrintOneTaskInDetails(list.tasks[taskNumberToEdit-1]);
      cout<<endl;
      option=(enEdit)PositiveShortNumberInRange("1. Edit Title\n2. Edit Description\n3. Edit Priority\n4. Cancel\n\nChoose the option:",1,4);
      EditOneParameter(option,list.tasks[taskNumberToEdit-1]);
      if(option!=enEdit::Cancel){
        cout<<"+++ Task edited successfully. +++\n";
      }

     }else{
        cout<<"You do not have tasks to edit!\n";
     }
}
void Pause (){
    cout<<"\nPress Enter to return to main menu...";
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
     cin.get();

}
void ExecuteSelectedOption(stToDoList &list){
    switch(list.currentOperation)
    {
    case enOperation::Exit:
       ConfirmExit(list.currentOperation);
        break;
    case enOperation::Add:
       AddTaskInList(list) ;
       break ;
    case  enOperation::ViewAll :
       ViewAllList(list) ;
       break;
    case enOperation::ViewPending :
      ViewPendingTasks(list);
      break;
    case enOperation::ViewCompleted :
      ViewCompletedTasks(list);
      break;    
    case enOperation::ViewTaskDetails:
      ViewTask(list);
      break;
    case enOperation::Edit:
      EditTask(list);
      break;
    case enOperation::MarkDone :
      MarkAsCompleted(list) ;
      break ;
    case enOperation::MarkPending :
      MarkAsPending(list);
      break;
    case enOperation::DeleteTask :
       DeleteOneTask(list) ; 
       break ;
    case enOperation::DeleteAllTasks :
      DeleteAll(list);
      break ;
    default:
        break;
    }
    if(list.currentOperation!=enOperation::Exit){
        Pause();
    }

}
void StartToDOListManager(){
    stToDoList list ;
 do{ 
    cout<<endl ;
    PrintMainMenu(list);
    list.currentOperation=(enOperation)PositiveShortNumberInRange("Choose the option :",1,11);
    cout<<endl;
    ExecuteSelectedOption(list) ;
}while (list.currentOperation!=enOperation::Exit);
}

int main (){
    StartToDOListManager();
    return 0 ;
}

