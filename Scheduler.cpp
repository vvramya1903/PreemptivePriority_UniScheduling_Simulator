#include <queue>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
class jobs
{
  public:
    int idNum;      
    int arrival;    
    int priority;  
    int cpuTime;    
    int cpuLeft;    
    int cpuDone;    
    int completed; 
    int currRR;     

    jobs() {}

    jobs(int id, int arriv, int pri, int cpuT)
    {
        idNum = id;
        arrival = arriv;
        priority = pri;
        cpuTime = cpuT;
        cpuLeft = cpuT;
        cpuDone = 0;
        cpuLeft = 0;
        completed = 0;
        currRR = 0;
    }

    ~jobs() {}
};

struct ComparePriority
{
    bool operator()(const jobs &p1, const jobs &p2)
    {
        return p1.priority > p2.priority; 
    }
};


int getNumberOfJobs(); 
void getJobAttributes(vector<jobs> &vec, int n); 
void emitVector( const vector<jobs> v); 
int getTotalTime( vector<jobs> &v); 
void checkArrivals( vector<jobs> v, int t); 
void checkPQ(); 
void emitTime(int t); 
void check4Preempt(int tempID); 
void check4Tie(); 
void turnAroundTimes( vector<jobs> v);
void check4Exit(int t, int bigT,vector<jobs> &v);
void ganttyOnDude(int bigT, vector<jobs> v); 
void ludacrisSpeed(); 

priority_queue<jobs, vector<jobs>, ComparePriority> PQ;
int prevRR;
int selector = 1;

int getNumberOfJobs()
{
    int number;
    cout << "# of jobs: ";
    cin >> number;
    cout << number << endl;
    return number;
}

void getJobAttributes(vector<jobs> &vec, int n)
{
    int ar, pri, cpu;
    for (int i = 0; i < n; i++)
    {
        cout << endl
             << "Job: " << i;
        cout << endl
             << "Arrival: ";
        cin >> ar;
        cout << ar << endl
             << "Priority: ";
        cin >> pri;
        cout << pri << endl
             << "cpuTime: ";
        cin >> cpu;
        cout << cpu << endl;
        jobs newJob(i, ar, pri, cpu);
        newJob.cpuLeft = newJob.cpuTime;
        vec.push_back(newJob);
    }
}
void emitVector(const vector<jobs> v)
{
    cout << endl
         << "Job Chart" << endl
         << "#  Ar Pr CT CL CD NN" << endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].idNum << "  "
             << v[i].arrival << "  "
             << v[i].priority << "  "
             << v[i].cpuTime << "  "
             << v[i].cpuLeft << "  "
             << v[i].cpuDone << "  "
             << v[i].completed
             << endl;
    }
    cout << endl;
}

/*
adds the total time needed to complete all jobs
sum of all cpuTimes
*/
int getTotalTime(vector<jobs> &v)
{
    int bigT = 0;
    for (int i = 0; i < v.size(); i++)
    {
        bigT += v.at(i).cpuTime;
    }
    return bigT;
}


bool isEmpty()
{
    if (PQ.empty())
    {
        return true;
    }
    return false;
}

void checkArrivals(vector<jobs> v, int t)
{
    jobs temp;
    int preemptJobNum;
    if (!isEmpty())
    {
        preemptJobNum = PQ.top().idNum;
    }
    for (int i = 0; i < v.size(); i++) 
    {
        if (v.at(i).arrival == t) 
        {
            cout << "job: " << v.at(i).idNum << " arrives" << endl;
            temp = v.at(i);
            if (!isEmpty())
            {
                if (temp.priority < PQ.top().priority)
                {
                    cout << "Context switch"
                         << endl
                         << "job " << preemptJobNum << " preempts" << endl;
                }
            }
            PQ.push(temp);
        }
    }
}

void checkPQ()
{
    if (!isEmpty())
    {
        int tempID = PQ.top().idNum;
        jobs temp = PQ.top();
        cout << "job: " << tempID << " runs" << endl;
        PQ.pop();
        
        temp.cpuDone++;
        temp.cpuLeft--;
        temp.currRR++;
        PQ.push(temp);

        while ((PQ.top().idNum != temp.idNum))
        {
            jobs placeholder = PQ.top();
            PQ.pop();
            PQ.push(placeholder);
        }
    }
}


void emitTime(int t)
{
    cout << "\n-----------------"
         << "\n|   Time = " << t
         << "   |"
         << "\n-----------------" << endl;
}

void check4Preempt(int tempID)
{
    cout << "job: " << tempID << " preempts" << endl;
}


void check4Tie()
{
    if (PQ.top().currRR > 1) 
    {
        jobs temp = PQ.top();
        int tempID = temp.idNum;
        PQ.pop();
        if ((PQ.top().priority == temp.priority) && (PQ.top().idNum != temp.idNum))
        {
            temp.currRR = 0;
            PQ.push(temp);
            check4Preempt(tempID);
        }
        else 
        {
            PQ.push(temp);
        }
    }
}


void turnAroundTimes(vector<jobs> v)
{
    float avgTaT = 0;
    cout << "\n---------------------------\n"
         << "|    Turn Around Times    |\n"
         << "---------------------------" << endl;
    cout << "job "
         << "n Tat: T(f) - T(i) = xx\n"
         << "---------------------------" << endl;
    for (int i = 0; i < v.size(); i++) 
    {
        float jobTaT = v.at(i).completed - v.at(i).arrival;
        avgTaT += jobTaT;
        cout << "job " << i << " Tat:  "
             << v.at(i).completed << "  -  " << v.at(i).arrival << "  =  " << jobTaT << endl;
    }
    cout << "---------------------------\n"
         << "      AVG TaT: " << avgTaT / v.size()
         << "\n---------------------------\n"
         << endl;
}

void check4Exit(int t, int bigT, vector<jobs> &v)
{
    if (!isEmpty())
    {
        jobs temp = PQ.top();
        int tempID = temp.idNum;
        if (temp.cpuLeft == 0) 
        {
            PQ.pop();
            cout << "job: " << tempID << " completed" << endl;
            for (int i = 0; i < v.size(); i++)
            {
                if (v.at(i).idNum == tempID)
                {
                    v.at(i).completed = t;
                }
            }
            if (isEmpty()) 
            {
                check4Exit(t, bigT, v);
            }
            else 
            {
                cout << "Context switch" << endl;
            }
        }
    }
    else 
    {
        if (t < bigT) 
        {
            cout << "Empty CPU cycle" << endl;
        }
        else 
        {
            cout << "***Queue empty***" << endl;
            turnAroundTimes(v);
            exit(0);
        }
    }
}

void ganttyOnDude(int bigT, vector<jobs> v)
{
    for (int t = 0; t <= bigT; t++)
    {
        sleep(selector);      
        emitTime(t);          
        checkArrivals(v, t);    
        check4Exit(t, bigT, v); 
        check4Tie();            
        checkPQ();            
        if (!isEmpty() && t == bigT)
        {
            bigT++;
        }
    }
}

void Speed()
{
    cout << "How many second(s) delay between time units; 0 - 9 seconds?: ";
    cin >> selector;
    cout << selector << endl
         << endl;
    if ((selector < 0) || (selector > 9))
    {
        cout << "please enter a valid response" << endl;
        Speed();
    }
}

int main()
{
    Speed();
    int n = getNumberOfJobs();
    vector<jobs> jobVec;
    getJobAttributes(jobVec, n);
    emitVector(jobVec);
    int time = getTotalTime(jobVec);
    ganttyOnDude(time, jobVec);

    return 0;
}