// C++ implementation of the SJF preemptive algorithm
#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

class process {
public:
	pid_t p_no = 0;
	time_t start_AT = 0, AT = 0,
		BT_left = 0, BT = 0, temp_BT = 0,
		CT = 0, TAT = 0, WT = 0, RT = 0;
	int priority = 0;

	// Function for completion time
	void set_CT(time_t time)
	{
		CT = time;
		set_TAT();
		set_WT();
	}

	// Function for Turn Around Time
	void set_TAT()
	{
		TAT = CT - start_AT;
	}

	// Function for Waiting Time
	void set_WT()
	{
		WT = TAT - BT;
	}
	void P_set()
	{
		start_AT = AT;
		BT_left = BT;
	}
	void set_RT(time_t time)
	{
		RT = time - start_AT;
	}

	// Overload operator '<' w.r.t arrival
	// time because arrival time is the
	// first priority even greater than
	// priority of process and priority_queue
	// pops out the greatest value first
	// so we need to replace '<' with '>' inorder
	// to pop out smallest value
	friend bool operator<(const process& a, const process& b)
	{
		return a.AT > b.AT;
	}
};

process pop_index(priority_queue<process>* main_queue, int index)
{
	priority_queue<process> rm_index;
	int i;
	process p;
	switch (index) {
	case 0:
		p = (*main_queue).top();
		(*main_queue).pop();
		break;
	default:
		for (i = 0; i < index; i++) {
			rm_index.push((*main_queue).top());
			(*main_queue).pop();
		}
		p = (*main_queue).top();
		(*main_queue).pop();
		while (!(*main_queue).empty()) {
			rm_index.push((*main_queue).top());
			(*main_queue).pop();
		}
		(*main_queue) = rm_index;
		break;
	}
	return p;
}
time_t min_BT(priority_queue<process> main_queue, time_t clock)
{
	time_t min = 0;
	while (!main_queue.empty() && main_queue.top().AT <= clock) {
		if (min == 0 || min > main_queue.top().BT_left)
			min = main_queue.top().BT_left;
		main_queue.pop();
	}
	return min;
}
int min_BT_index(priority_queue<process> main_queue, time_t limit)
{
	int index, i = 0;
	time_t min = 0;
	while (!main_queue.empty() && main_queue.top().AT <= limit) {
		if (min == 0 || main_queue.top().BT_left < min) {
			min = main_queue.top().BT_left;
			index = i;
		}
		main_queue.pop();
		i++;
	}
	return index;
}

// Function to implement SJF preemptive algorithm
priority_queue<process> SJF_P_run(priority_queue<process> ready_queue,
								queue<process>* gantt)
{
	priority_queue<process> completion_queue;
	process p;
	time_t clock = 0;

	while (!ready_queue.empty()) {
		while (clock < ready_queue.top().AT) {
			p.temp_BT++;
			clock++;
		}
		if (p.temp_BT > 0) {
			p.p_no = -1;
			p.CT = clock;
			(*gantt).push(p);
		}
		p = pop_index(&ready_queue, min_BT_index(ready_queue, clock));
		if (p.AT == p.start_AT)
			p.set_RT(clock);
		while (p.BT_left > 0 && (ready_queue.empty()
			    || clock < ready_queue.top().AT
				|| p.BT_left <= min_BT(ready_queue, clock))) {
			p.BT_left--;
			p.temp_BT++;
			clock++;
		}
		if (p.BT_left == 0) {
			p.AT = p.start_AT;
			p.set_CT(clock);
			(*gantt).push(p);
			p.temp_BT = 0;
			completion_queue.push(p);
		}
		else {
			p.AT = clock;
			p.CT = clock;
			(*gantt).push(p);
			p.temp_BT = 0;
			ready_queue.push(p);
		}
	}

	return completion_queue;
}

// Set data on the basis of given table
priority_queue<process> set_sample_data()
{
	priority_queue<process> ready_queue;
	process temp;
	int a;
	printf("Enter the No of processes: ");
	scanf("%d",&a);
	for(int i=0;i<a;i++){
	    printf("Enter the Process No : ");
	    scanf("%d",&temp.p_no);
	    printf("Enter the Arrival time of %d Process: ",i+1);
	    scanf("%ld",&temp.AT);
	    printf("Enter the Burst time of %d Process: ",i+1);
	    scanf("%ld",&temp.BT);
	    printf("Enter the Priority(High Value High Priority) of %d Process: ",i+1);
	    scanf("%d",&temp.priority);
	    temp.P_set();
	    ready_queue.push(temp);
	    printf("\n");
	}

	return ready_queue;
}

// Function to get total Waiting Time
double get_total_WT(priority_queue<process> processes)
{
	double total = 0;
	while (!processes.empty()) {
		total += processes.top().WT;
		processes.pop();
	}
	return total;
}

// Function to get total Turn Around Time
double get_total_TAT(priority_queue<process> processes)
{
	double total = 0;
	while (!processes.empty()) {
		total += processes.top().TAT;
		processes.pop();
	}
	return total;
}

// Function to get total Completion Time
double get_total_CT(priority_queue<process> processes)
{
	double total = 0;
	while (!processes.empty()) {
		total += processes.top().CT;
		processes.pop();
	}
	return total;
}

// Function to get total Response Time
double get_total_RT(priority_queue<process> processes)
{
	double total = 0;

	while (!processes.empty()) {
		total += processes.top().RT;
		processes.pop();
	}
	return total;
}

// Function to display Completion Queue
// and all the time
/*void disp(priority_queue<process> main_queue, bool high)
{
	int i = 0, temp, size = main_queue.size();
	priority_queue<process> tempq = main_queue;
	double temp1;
	cout << "+-------------+--------------";
	cout << "+------------+-----------------";
	cout << "+-----------------+--------------+----------+";
	if (high == true)
		cout << " " << endl;
	else
		cout << endl;
	cout << "| Process No. | Arrival Time ";
	cout << "| Burst Time | Completion Time ";
	cout << "| Turnaround Time | Waiting Time | Priority |";
	if (high == true)
		cout << " Priority |" << endl;
	else
		cout << endl;
	cout << "+-------------+--------------";
	cout << "+------------+-----------------";
	cout << "+-----------------+--------------+----------+";
	if (high == true)
		cout << " " << endl;
	else
		cout << endl;
	while (!main_queue.empty()) {
		temp = to_string(main_queue.top().p_no).length();
		cout << '|' << string(6 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().p_no << string(7 - temp / 2, ' ');
		temp = to_string(main_queue.top().start_AT).length();
		cout << '|' << string(7 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().start_AT << string(7 - temp / 2, ' ');
		temp = to_string(main_queue.top().BT).length();
		cout << '|' << string(6 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().BT << string(6 - temp / 2, ' ');
		temp = to_string(main_queue.top().CT).length();
		cout << '|' << string(8 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().CT << string(9 - temp / 2, ' ');
		temp = to_string(main_queue.top().TAT).length();
		cout << '|' << string(8 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().TAT << string(9 - temp / 2, ' ');
		temp = to_string(main_queue.top().WT).length();
		cout << '|' << string(7 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().WT << string(7 - temp / 2, ' ');
		temp = to_string(main_queue.top().RT).length();
	    temp = to_string(main_queue.top().priority).length();
		cout << '|' << string(5 - temp / 2 - temp % 2, ' ')
			<< main_queue.top().priority << string(5 - temp / 2, ' ');
		if (high == true) {
			temp = to_string(main_queue.top().priority).length();
			cout << '|' << string(5 - temp / 2 - temp % 2, ' ')
				<< main_queue.top().priority << string(5 - temp / 2, ' ');
		}
		cout << "|\n";
		main_queue.pop();
	}
	cout << "+-------------+--------------";
	cout << "+------------+-----------------";
	cout << "+-----------------+--------------+----------+";
	if (high == true)
		cout << " ";
	cout << endl;
	
}*/

void disp(priority_queue<process> main_queue, bool high)
{
    int i = 0, temp, size = main_queue.size();
    priority_queue<process> tempq = main_queue;
    double temp1;
    printf("+-------------+--------------");
    printf("+------------+-----------------");
    printf("+-----------------+--------------+----------+\n");
    if (high == true)
        printf("\n");
    else{}
        
    printf("| Process No. | Arrival Time ");
    printf("| Burst Time | Completion Time ");
    printf("| Turnaround Time | Waiting Time | Priority |");
    if (high == true)
        printf(" Priority |\n");
    else
        printf("\n");
    printf("+-------------+--------------");
    printf("+------------+-----------------");
    printf("+-----------------+--------------+----------+\n");
    while (!main_queue.empty()) {
        temp = to_string(main_queue.top().p_no).length();
        printf("|%s%d%s", string(6 - temp / 2 - temp % 2, ' ').c_str(), main_queue.top().p_no, string(7 - temp / 2, ' ').c_str());
        temp = to_string(main_queue.top().start_AT).length();
        printf("|%s%ld%s", string(7 - temp / 2 - temp % 2, ' ').c_str(), main_queue.top().start_AT, string(7 - temp / 2, ' ').c_str());
        temp = to_string(main_queue.top().BT).length();
        printf("|%s%ld%s", string(6 - temp / 2 - temp % 2, ' ').c_str(), main_queue.top().BT, string(6 - temp / 2, ' ').c_str());
        temp = to_string(main_queue.top().CT).length();
        printf("|%s%ld%s", string(8 - temp / 2 - temp % 2, ' ').c_str(), main_queue.top().CT, string(9 - temp / 2, ' ').c_str());
        temp = to_string(main_queue.top().TAT).length();
        printf("|%s%ld%s", string(8 - temp / 2 - temp % 2, ' ').c_str(), main_queue.top().TAT, string(9 - temp / 2, ' ').c_str());
        temp = to_string(main_queue.top().WT).length();
        printf("|%s%ld%s", string(7 - temp / 2 - temp % 2, ' ').c_str(), main_queue.top().WT, string(7 - temp / 2, ' ').c_str());
        temp = to_string(main_queue.top().RT).length();
        temp = to_string(main_queue.top().priority).length();
        printf("|%s%d%s", string(5 - temp / 2 - temp % 2, ' ').c_str(), main_queue.top().priority, string(5 - temp / 2, ' ').c_str());
        if (high == true) {
            temp = to_string(main_queue.top().priority).length();
            printf("|%s%d%s", string(5 - temp / 2 - temp % 2, ' ').c_str(), main_queue.top().priority, string(5 - temp / 2, ' ').c_str());
        }
        printf("|\n");
        main_queue.pop();
    }
    printf("+-------------+--------------");
    printf("+------------+-----------------");
    printf("+-----------------+--------------+----------+\n");
    if (high == true)
        printf(" ");
    printf("\n");
}


// Function to display Gantt Chart
/*void disp_gantt_chart(queue<process> gantt)
{
	int temp, prev = 0;
	queue<process> spaces = gantt;
	cout << "\n\nGantt Chart :- \n\n+";

	while (!spaces.empty()) {
		cout << string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT, '-') << "+";
		spaces.pop();
	}
	cout << "\n|";
	spaces = gantt;

	while (!spaces.empty()) {
		cout << string(spaces.front().temp_BT, ' ');
		if (spaces.front().p_no == -1)
			cout << "IS" << string(spaces.front().temp_BT, ' ') << '|';
		else
			cout << "P" << spaces.front().p_no
				<< string(spaces.front().temp_BT, ' ') << '|';
		spaces.pop();
	}
	spaces = gantt;
	cout << "\n+";

	while (!spaces.empty()) {
		cout << string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT, '-')
			<< "+";
		spaces.pop();
	}
	spaces = gantt;
	cout << "\n0";

	while (!spaces.empty()) {
		temp = to_string(spaces.front().CT).length();
		cout << string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT
						- temp / 2 - prev,
					' ')
			<< spaces.front().CT;
		prev = temp / 2 - temp % 2 == 0;
		spaces.pop();
	}

	cout << "\n\n";
}*/
void disp_gantt_chart(queue<process> gantt)
{
    int temp, prev = 0;
    queue<process> spaces = gantt;
    printf("\n\nGantt Chart :- \n\n+");
    
    while (!spaces.empty()) {
        printf("%s+", string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT, '-').c_str());
        spaces.pop();
    }
    printf("\n|");
    spaces = gantt;
    
    while (!spaces.empty()) {
        printf("%s", string(spaces.front().temp_BT, ' ').c_str());
        if (spaces.front().p_no == -1)
            printf("IS%s|", string(spaces.front().temp_BT, ' ').c_str());
        else
            printf("P%d%s|", spaces.front().p_no, string(spaces.front().temp_BT, ' ').c_str());
        spaces.pop();
    }
    spaces = gantt;
    printf("\n+");
    
    while (!spaces.empty()) {
        printf("%s+", string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT, '-').c_str());
        spaces.pop();
    }
    spaces = gantt;
    printf("\n0");
    
    while (!spaces.empty()) {
        temp = to_string(spaces.front().CT).length();
        printf("%s%ld", string(to_string(spaces.front().p_no).length() + (spaces.front().p_no != -1) + 2 * spaces.front().temp_BT - temp / 2 - prev, ' ').c_str(), spaces.front().CT);
        prev = temp / 2 - temp % 2 == 0;
        spaces.pop();
    }
    
    printf("\n\n");
}


// Driver Code
int main()
{
	// Initialize Ready and Completion Queue
	priority_queue<process> ready_queue, completion_queue;

	// queue for Gantt Chart
	queue<process> gantt;
	ready_queue = set_sample_data();

	// Function call for completion data
	completion_queue = SJF_P_run(ready_queue, &gantt);

	// Display Completion Queue
	disp(completion_queue, false);

	// Display Gantt Chart
	disp_gantt_chart(gantt);
	return 0;
}



