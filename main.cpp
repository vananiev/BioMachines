//---------------------------------------------------------------------------
#include <vcl.h>
#include "main.h"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TF *F;
void paint_zoom();
void delete_shape();
void add_shape();
#include <animal.h>
typedef TShape* PShape;
PShape *shape = new PShape[mN];      //�������� ����������� ��� �������
int x1=0;       //���������� ��������� ����� �� ��������� Gr[�1][][]
int x2=0;       //���������� ������ �� ������� �2
int x3=0;       //���������� ��������� ������� �� ���������
int w=W;        //������ ���� � ��
int w0=0;       //�������� ������ ������� �� � � ��
int h=H;        //������ ���� � ��
int h0=0;       //�������� ������ ������� �� � � ��
bool zooming=false;        //���������� �������� �������� ��� ������� �� ctrl
char name[1024][64]; //���������� ���������� � A[][][]
//---------------------------------------------------------------------------
__fastcall TF::TF(TComponent* Owner)
        : TForm(Owner)
{
}
//------------����������� ���������� ���������� �������� �����������--------
void __fastcall TF::TimerTimer(TObject *Sender)
{
        randomize;
        //���������� ������������
        for(int n=0;n<N;n++)
                {
                for(int p=0;p<Pi;p++)
                        {
                        //����������� ���������� ���������� �������� �����������
                        if(X[n].B[p]-X[n].A[p]>=0)
                                Do(n,X[n].D[p],X[n].W[p]);
                                else
                                Do(n,X[n].nD[p],X[n].W[p]);
                        }
                }
        //������� ������������ � ����� ����
        for(int n=0;n<N;n++)
                {
                for(int p=0;p<Po;p++)
                        {
                        //����������� ���������� ���������� �������� �����������
                        if(E.Gr[p][I/W*(int)X[n].x][J/H*(int)X[n].y]-X[n].A[p+Pp]>=0)
                                Do(n,X[n].D[p+Pp],X[n].W[p+Pp]);
                                else
                                Do(n,X[n].nD[p+Pp],X[n].W[p+Pp]);
                        }
                }
        for(int n=0;n<N;n++)
                {
                //��������
                action(n);
                if(X[n].x<0) X[n].x=0;
                if(X[n].x>0.9*W) X[n].x=0.9*W;
                if(X[n].y<0) X[n].y=0;
                if(X[n].y>0.9*H) X[n].y=0.9*H;
                //����������
                shape[n]->Top=(float)F->Height/h*(X[n].y-h0);
                shape[n]->Left=(float)F->Width/w*(X[n].x-w0);
                //���������� � ����������� ��������
                if(!zooming){
                        shape[n]->Height=1+2*(float)F->Height/w*pow(X[n].B[1],0.33);//���������� � ��������
                        shape[n]->Width=shape[n]->Height;}
                        else{
                        shape[n]->Height=8;
                        shape[n]->Width=shape[n]->Height;}
                }
}
//--------------------------------------------------------------------------
void __fastcall TF::N11Click(TObject *Sender)
{
        x1=1;
}
//---------------------------------------------------------------------------
void __fastcall TF::N4Click(TObject *Sender)
{
        x1=StrToInt(InputBox("������� �������� ��� ������","",0));
        if(x1>Po) x1=Po-1;
}
//---------------------------------------------------------------------------

void __fastcall TF::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
                SBar->Panels->Items[0]->Text=name[x1+Pp];
                SBar->Panels->Items[1]->Text=FloatToStr((int)(E.Gr[x1][(int)(1.0*I/W*(w0+w*(1.0*X/F->Width)))][(int)(1.0*J/H*(h0+h*(1.0*Y/F->Height)))]*10e5)/10e5).c_str();
                SBar->Panels->Items[2]->Text=IntToStr((int)(w0+w*(1.0*X/F->Width)));      //���������� �  � ��
                SBar->Panels->Items[3]->Text=IntToStr((int)(h0+h*(1.0*Y/F->Height)));     //���������� �  � ��
}
//---------------------------------------------------------------------------
void __fastcall TF::tmrInfTimer(TObject *Sender)
{
        Inf->Clear();
        if(x2>=N)
                  Inf->Lines->Add("�����");
        Inf->Lines->Add("����� �������,(��) ");
        Inf->Lines->Add(FloatToStr(X[x2].B[0]).c_str());
        Inf->Lines->Add("������,(��) ");
        Inf->Lines->Add(FloatToStr(pow(X[x2].B[1],0.33)).c_str());
        Inf->Lines->Add("�����,(��) ");
        Inf->Lines->Add(FloatToStr(X[x2].B[1]).c_str());
        Inf->Lines->Add("����� �����,(�) ");
        Inf->Lines->Add(FloatToStr(X[x2].B[4]).c_str());
        if(X[x2].B[5]==0)
                Inf->Lines->Add("�� ������");
                else
                Inf->Lines->Add("������");

}
//---------------------------------------------------------------------------
void __fastcall TF::FormResize(TObject *Sender)
{
        Inf->Left=F->Width-Inf->Width;
        Inf->Height=F->Height-SBar->Height-60;
        pAll->Left=8;
        pAll->Top=F->Height-pAll->Height-SBar->Height-60;
}
//---------------------------------------------------------------------------
void __fastcall TF::FormCreate(TObject *Sender)
{
        char temp[255];
        //�������� �����������
        for( int i = 0; i < mN; ++i )
                {
                shape[i] = new TShape( this );
                shape[i]->Left=-100;
                shape[i]->Visible=false;
                shape[i]->Shape=stCircle;
                shape[i]->Height=10;
                shape[i]->Tag=i;   //����� ��� ����������
                shape[i]->Parent=F;      //delete ��� ��������
                shape[i]->OnMouseUp=ShapeMouseUp;
                }
        randomize;
        //F->Timer->Interval=tmr;
        F->Timer->Enabled=True;
        //������� ���������� ���������� �����
        for(int i=0;i<I;i++)
                for(int j=0;j<J;j++)
                        {E.Gr[1][i][j]=21;              //���������� ��������� %
                        E.Gr[0][i][j]=2.0/(I*J);}       //����� 2 �� ����������� �-�
         //�������� ���������
         ifstream in("���������.txt");
         if(!in)
                ShowMessage("�� ������� ������� ���� ���������.txt.");
         for(int n=0;n<Pn;n++)
                in>>name[n];
         in.close();
        for(int n=0;n<N;n++)
                {
                //���������� ���
                ifstream in("dnk.txt");
                        if(!in)
                        ShowMessage("�� ������� ������� ���� ��� ��� (dnk.txt).");
                for(int p=0;p<Pn;p++)
                        {
                        in>>temp;
                        in>>X[n].A[p];
                        in>>X[n].D[p];
                        in>>X[n].nD[p];
                        in>>X[n].W[p];
                        in>>X[n].B[p];
                        }
                //��������� ��������� ����������
                X[n].B[5]=random(2);     //0-���������� �� ������, 1-������
                X[n].Vq=M_PI*random(360)/180;
                X[n].Vmax=0.2;
                X[n].Vflag=1;
                X[n].t=0;
                X[n].x=500+(random(31)-1);
                X[n].y=500+(random(31)-1);
                X[n].prp.x=random(W-30);   //����
                X[n].prp.y=random(H-30);
                shape[n]->Top=(float)F->Height/W*X[n].y;
                shape[n]->Left=(float)F->Width/H*X[n].x;
                shape[n]->Visible=true;
                in.close();
                }
}
//---------------------------------------------------------------------------
void __fastcall TF::ShapeMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        //�������������� �������
        shape[x2]->Brush->Color=clWhite;
        x2=((TShape *)Sender)->Tag;     //����� �������, ������� ������ �����
        //��������� ����� ����� � N5Click(Sender)
        N5->Checked=False;
        N5Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TF::FormMouseWheel(TObject *Sender, TShiftState Shift,
      int WheelDelta, TPoint &MousePos, bool &Handled)
{
        int S=1;
        if(Shift==TShiftState() << ssShift) S=(int)(1.0*w/10);
        //�������������� ����
        w=w-2*S*(WheelDelta/abs(WheelDelta));
        h=h-2*S*(WheelDelta/abs(WheelDelta));
        w0+=1*S*(WheelDelta/abs(WheelDelta));
        h0+=1*S*(WheelDelta/abs(WheelDelta));
        if(w0+w>W) w0=W-w;
        if(w0<0) w0=0;
        if(h0+h>H) h0=H-h;
        if(h0<0) h0=0;
        if(w<1) w=1;
        if(w>W) w=W;
        if(h<1) h=1;
        if(h>H) h=H;
        paint_zoom();
}
//---------------------------------------------------------------------------

void __fastcall TF::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        int S=1;
        if(Shift==TShiftState() << ssShift) S=10;
        switch(Key){
                case 39: w0+=1*S;
                        if(w0+w>W) w0=W-w;
                        paint_zoom();
                        break;
                case 37: w0-=1*S;
                        if(w0<0) w0=0;
                        paint_zoom();
                        break;
                case 40: h0+=1*S;
                        if(h0+h>H) h0=H-h;
                        paint_zoom();
                        break;
                case 38: h0-=1*S;
                        if(h0<0) h0=0;
                        paint_zoom();
                        break;
                case 17: zooming=true;}         //������� ctrl
}
//---------------------------------------------------------------------------
void paint_zoom()
{
        //�������������� ������ � �����
        char *t="";
        int l;
        double z=1.0*W/w;
        t[0]=0;
        strcat(t,IntToStr((int)z).c_str());
        l=strlen(t);
        t[l]='.';
        z=10*(z-(int)z);
        t[l+1]=48+int(z);
        t[l+2]='x';
        t[l+3]=0;
        F->Caption=t;
        //����������
        F->pAll->Visible=True;
        float zoom_w=1.0*F->pAll->Width/W;
        float zoom_h=1.0*F->pAll->Height/H;
        F->pScr->Width=zoom_w*w;
        F->pScr->Height=zoom_h*h;
        F->pScr->Left=zoom_w*w0;
        F->pScr->Top=zoom_h*h0;
        F->tmrSlide->Enabled=True;
}

void __fastcall TF::tmrSlideTimer(TObject *Sender)
{
        pAll->Visible=False;
        tmrSlide->Enabled=False;
}
//---------------------------------------------------------------------------
void __fastcall TF::N5Click(TObject *Sender)
{
        //������� ������� �� ��������� ��������
        if(N9->Checked)
                N9Click(Sender);
        N5->Checked=!N5->Checked;
        Inf->Visible=N5->Checked;
        tmrInf->Enabled=N5->Checked;
        if(N5->Checked)
                shape[x2]->Brush->Color=clLime;
                else
                shape[x2]->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TF::N6Click(TObject *Sender)
{
        //�������������� �������
        shape[x2]->Brush->Color=clWhite;
        //����� �������
        x2=StrToInt(InputBox("������� ����� �������","",0));
        if(x2>=N)  x2=N-1;
        float w_z=(float)F->Width/5*pow(X[x2].B[1],0.33); //������ �������� �� �
        float h_z=(float)F->Height/5*pow(X[x2].B[1],0.33); //������ �������� �� �
        (w_z>h_z)?w_z=h_z:w_z=w_z;
        float z=w_z/w;
        w=w*z;
        h=h*z;
        w0=X[x2].x-1.0*w/2;
        h0=X[x2].y-1.0*h/2;
        paint_zoom();
        //��������� ����� ����� � N5Click(Sender)
        N5->Checked=False;
        N5Click(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TF::N7Click(TObject *Sender)
{
        char sname[64];
        strcpy(sname,InputBox("������� ��� ����������","","default").c_str());
        //Save ���������� ���������� �����
        char nm[32]="save/env_";
        ofstream out(strcat(strcat(nm,sname),".txt"));
        if(out)
                {out<<Po<<endl;
                out<<I<<endl;
                out<<J<<endl;
                for(int n=0 ;n<Po;n++)
                        {for(int i=0;i<I;i++)
                                {for(int j=0;j<J;j++)
                                        out<<E.Gr[n][i][j]<<" ";
                                out<<endl;}
                        out<<endl;}
                out.close();}
                else
                ShowMessage("�� ������� ������� ����.");

        for(int n=0;n<N;n++)
                {char nm[32]="save/dnk_";
                ofstream out(strcat(strcat(strcat(nm,sname),IntToStr(n).c_str()),".txt"));
                if(out)
                        {out<<X[n].x<<endl;
                        out<<X[n].y<<endl ;
                        out<<X[n].Vmax<<endl;
                        out<<X[n].Vflag<<endl;
                        out<<X[n].V<<endl;
                        out<<X[n].Vq<<endl;
                        out<<X[n].prp.x<<endl;
                        out<<X[n].prp.y<<endl;
                        out<<X[n].t<<endl;
                        for(int p=0;p<Pn;p++)
                                {out<<X[n].A[p]<<"\t";
                                out<<X[n].D[p]<<"\t";
                                out<<X[n].nD[p]<<"\t";
                                out<<X[n].W[p]<<"\t";
                                out<<X[n].B[p]<<endl;
                                }
                        out.close();
                        }
                        else
                        ShowMessage("�� ������� ������� ����.");
                }
}
//---------------------------------------------------------------------------
void __fastcall TF::N8Click(TObject *Sender)
{
        char sname[64];
        char nm[32]="save/env_";
        strcpy(sname,InputBox("������� ��� ����������","","default").c_str());
        ifstream in(strcat(strcat(nm,sname),".txt"));
        if(in)
                {int temp;
                in>>temp;
                in>>temp;
                in>>temp;
                for(int n=0 ;n<Po;n++)
                        for(int i=0;i<I;i++)
                                for(int j=0;j<J;j++)
                                        in>>E.Gr[n][i][j];
                in.close();}
                else
                ShowMessage("�� ������� ������� ����.");
        bool flag=true;
        for(int n=0;n<mN && flag;n++)
                {char nm[32]="save/dnk_";
                ifstream in(strcat(strcat(strcat(nm,sname),IntToStr(n).c_str()),".txt"));
                if(in)
                        {in>>X[n].x;
                        in>>X[n].y;
                        in>>X[n].Vmax;
                        in>>X[n].Vflag;
                        in>>X[n].V;
                        in>>X[n].Vq;
                        in>>X[n].prp.x;
                        in>>X[n].prp.y;
                        in>>X[n].t;
                        for(int p=0;p<Pn;p++)
                                {in>>X[n].A[p];
                                in>>X[n].D[p];
                                in>>X[n].nD[p];
                                in>>X[n].W[p];
                                in>>X[n].B[p];
                                }
                        in.close();
                        }
                        else{
                        flag=false;
                        N=n;}
                }
                //��������� �������� ��� �����
                for(int n=0;n<mN;n++)
                {
                        if(n<N)
                                shape[n]->Visible=true;
                                else
                                shape[n]->Visible=false;
                        shape[n]->Tag=n;
                }
}
//---------------------------------------------------------------------------

void __fastcall TF::N9Click(TObject *Sender)
{
        //������� ������� �� ��������� �������
        if(N5->Checked)
                N5Click(Sender);
        //
        N9->Checked=!N9->Checked;
        //���������� �����
        if(N9->Checked)
                {SBar->Panels->Items[4]->Text=name[x3];
                for(int n=0;n<N;n++)
                        if(X[n].A[x3]!=0 && X[n].B[x3]!=0)
                                shape[n]->Brush->Color=(int)(255*(2*atan((float)X[n].A[x3]/X[n].B[x3])/M_PI)) +    //������� ������������
                                                        ((int)(255*(2*atan((float)X[n].B[x3]/X[n].A[x3])/M_PI))<<8);  //������� ������������
                                else if(X[n].A[x3]==0)
                                        shape[n]->Brush->Color=clLime;     //�������
                                else if(X[n].B[x3]==0)
                                        shape[n]->Brush->Color=clRed;        //�������
                }
                else
                {SBar->Panels->Items[4]->Text="";
                for(int n=0;n<N;n++)
                           shape[n]->Brush->Color=clWhite;
                }
}
//---------------------------------------------------------------------------

void __fastcall TF::N10Click(TObject *Sender)
{
        x3=StrToInt(InputBox("������� �������� ��� ������","",0));
        if(x1>Pn) x1=Pn-1;
        N9->Checked=False;
        N9Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TF::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        switch(Key){
                case 17: zooming=false;}         //������� ������� ctrl
}
//---------------------------------------------------------------------------
void delete_shape()
{
        shape[N-1]->Visible=false;
        //���������� ������
        if(F->N5->Checked){
                F->N5->Checked=false;
                F->N5Click(F);}
        if(F->N9->Checked){
                F->N9->Checked=false;
                F->N9Click(F);}

}
void add_shape()
{
        shape[N]->Visible=true;
        //���������� ������
        if(F->N5->Checked){
                F->N5->Checked=false;
                F->N5Click(F);}
        if(F->N9->Checked){
                F->N9->Checked=false;
                F->N9Click(F);}

}
