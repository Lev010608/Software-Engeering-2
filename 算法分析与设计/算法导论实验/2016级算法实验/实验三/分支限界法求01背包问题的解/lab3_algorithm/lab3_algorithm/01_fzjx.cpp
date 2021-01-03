#include <iostream>

using namespace std;
    //tree node

    typedef struct _treenode{

    //struct _treenode *liveNode; //��ڵ�

    double upperProfit; //�ڵ�ļ�ֵ�Ͻ�

    double profit; //�ڵ��ֵ*

    double weight; //�ڵ�����

    int level; //��ڵ��������������Ĳ����

    //bool left;

    }TreeNode;

    void initNode(TreeNode &node, double up, double p, double w, int lev)

    {

    node.upperProfit = up; node.profit = p; node.weight = w; node.level = lev;

    }

    ///////////////////////////////////////////////////////////////////////////////////

    #define MAX_LENGTH 20

    //class LQueue

    class LQueue{

    public:

    LQueue() {length = 0;}

    virtual ~LQueue(){}

    void addTail(TreeNode tn);

    TreeNode removeHead();

    TreeNode removeMax();

    TreeNode removeMin();

    int GetLength(){return length;}

    protected:

    private:

    //int queue[MAX_LENGTH];

    TreeNode queue[MAX_LENGTH]; //���0����ʼ�洢   

    int length; //�ڵ����

    };

    void LQueue::addTail(TreeNode tn)

    {

    queue[length++] = tn;

    }

    TreeNode LQueue::removeHead()

    {

    return queue[--length];

    }

    TreeNode LQueue::removeMax()

    {

    double max = 0.0;

    int num = -1;

    for (int i = 0; i < length; i++)

    {

    if (max < queue[i].profit)

    {

    max = queue[i].profit;

    num = i;

    }

    }

    TreeNode lq = queue[num];

    for (int j = num; j < (length-1); j++) //ɾ���ڵ�

    {

    queue[j] = queue[j+1];

    }

    length--;

    return lq;

    }

    TreeNode LQueue::removeMin() //�ó�����

    {

    return TreeNode();

    }

    ////////////////////////////////////////////////////////////////////////////////////

    #define ARRAY_LENGTH 4 //��Ʒ��

    LQueue queue;

    double w[] = {3, 5, 2, 1}; double p[] = {9, 10, 7, 4}; int sort[ARRAY_LENGTH];  //{3, 2, 0, 1}

    double c; //��������7

    double cw; //��ǰ����

    double cp; //��ǰ��ֵ

    double bestp; //��ǰ���ż�ֵ

    void init(double cc); //��ʼ��

    void sortpw(); //����Ʒ��λ������ֵ�ݼ���������洢��sort[]��   

    double bound(int i); //����i��ڵ��ֵ���Ͻ�(i: 0 ~ ARRAY_LENGTH-1)

    double bbKnapsack(); //��֧�޽編��0/1��������Ľ�

 int main()

    {

    init(7.0);

    sortpw();

    double max = bbKnapsack();

	cout<<endl;
	
	cout<<"������СΪ7������4����Ʒ������Ϊ3, 5, 2, 1����ֵΪ9, 10, 7, 4 "<<endl;

    cout<<endl<<endl<<"����ֵΪ��"<<max<<endl;

	//system("pause");
	return 0;

    }

    void init(double cc)

    {

    c = cc;

    cw = 0.0; cp = 0.0; bestp = 0.0;

    }

    void sortpw()

    {

    double pw[ARRAY_LENGTH];

    for (int i = 0; i < ARRAY_LENGTH; i++)

    {

    pw[i] = p[i] / w[i];

    }

    for (int i = 0; i < ARRAY_LENGTH; i++)

    {

    double max = 0.0;

    for (int j = 0; j < ARRAY_LENGTH; j++)

    {

    if (max < pw[j])

    {

    max = pw[j];

    sort[i] = j;

    }

    }

    pw[sort[i]] = 0.0;

    }

    }

    double bound(int i)

    {

    double cleft = c - cw;

    double b = cp;

    while (i < ARRAY_LENGTH && w[sort[i]] <= cleft)

    {

    cleft -= w[sort[i]];

    b += p[sort[i]];

    i++;

    }

    if (i < ARRAY_LENGTH)

    {

    b += p[sort[i]] / w[sort[i]] * cleft;

    }

    return b;

    }

    double bbKnapsack()

    {

    int i = 0; //��0�㿪ʼ

    double bestp = 0.0;

    double up = bound(0);

    while(i != ARRAY_LENGTH)

    {

    double wt = cw + w[sort[i]];

    if (wt <= c) //����ӽڵ�Ϊ���нڵ�

    {

    if (bestp < (cp+p[sort[i]]))

    {

    bestp = cp + p[sort[i]];

    }

    TreeNode *node = new TreeNode();

    initNode(*node, up, (cp+p[sort[i]]), (cw+w[sort[i]]), i+1); queue.addTail(*node);

    }

    up = bound(i+1);

    if (bestp <= up) //�Ҷ��ӽڵ�

    {

    TreeNode *node = new TreeNode();

    initNode(*node, up, cp, cw, i+1); queue.addTail(*node);

    }

    TreeNode tnode = queue.removeMax();

    cout<<tnode.weight<<"-"<<tnode.profit<<"  ";  //�����ǰ�ڵ�ļ�ֵ(��ֵ����)

    cw = tnode.weight; cp = tnode.profit; up = tnode.upperProfit; i = tnode.level;

    }

    return bestp;

    }
