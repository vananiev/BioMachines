void environment(int n,int p);
const I=100;
const J=100;
const Po=2;             //количество внешних раздражителей
short int W=1000;       //ширина поля, мм
short int H=1000;       //Высота поля, мм
//--------------------------------------------------------------------------
class envir{
        public:
        float Gr[Po][I][J]; //раздражитель (состояние среды)[номер][X][Y]
        };
envir E;
//------------Определение параметров среды----------------------------------
void environment(int n,int p)
{
       X[n].B[p]=E.Gr[p][I/W*(int)X[n].x][J/H*(int)X[n].y];
}
