void environment(int n,int p);
const I=100;
const J=100;
const Po=2;             //���������� ������� �������������
short int W=1000;       //������ ����, ��
short int H=1000;       //������ ����, ��
//--------------------------------------------------------------------------
class envir{
        public:
        float Gr[Po][I][J]; //������������ (��������� �����)[�����][X][Y]
        };
envir E;
//------------����������� ���������� �����----------------------------------
void environment(int n,int p)
{
       X[n].B[p]=E.Gr[p][I/W*(int)X[n].x][J/H*(int)X[n].y];
}
