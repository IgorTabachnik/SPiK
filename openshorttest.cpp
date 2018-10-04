#include "openshorttest.h"

QString DUTs[52] = {"DQ0_0","DQ1_0","DQ2_0","DQ3_0","DQ4_0","DQ5_0","DQ6_0","DQ7_0",
         "CE0_0#","CE1_0#","CE2_0#","CE3_0#","ALE_0","CLE_0#","WP_0#","WE_0",
        "DQS_0","DQS_0#","RE0#","RE0","R/B0_0#","R/B1_0#","ENi_0", "ENo_0",

        "DQ0_1","DQ1_1","DQ2_1","DQ3_1","DQ4_1","DQ5_1","DQ6_1","DQ7_1",
        "CE0_1#","CE1_1#","CE2_1#","CE3_1#","ALE_1","CLE_1#","WP_1#","WE_1",
        "DQS_1","DQS_1#","RE1#","RE1","R/B0_1#","R/B1_1#","Vref1", "Vref0","Vpp", "NotUse: ", "NotUse: ", "NotUse: "};

OpenShortTest::OpenShortTest(ExcelConfig *excel):
    excel(excel)
{

}

static float dw2float(uint16_t* ptr)
{
    float res=0;
    uint8_t* p = (uint8_t*)&res;

    p[0] = ptr[0]&0x00FF;
    p[1] = (ptr[0]>>8)&0x00FF;
    p[2] = ptr[1]&0x00FF;
    p[3] = (ptr[1]>>8)&0x00FF;

    return res;
}

void OpenShortTest::setPos_NEG(bool p_n)
{
    this->Pos_neg=p_n;
}

QString OpenShortTest::ProcessingResult(uint16_t* data, uint8_t Sel_MKM)
{
    QString res="";
    QString s_mal[4];
    uint8_t bit_MKM;
    for(uint8_t i=0;i<8;i++)
    {
        bit_MKM = 1<<i;
        if((Sel_MKM & bit_MKM)==bit_MKM)
        {
            res += QString("////MKM%1//// \r\n").arg(i+1);

            for(uint8_t j=0; j<13;j++){
                AnalyzeMalFunction(data[i*13+j],s_mal);
                if(j==12){
                    res += DUTs[j*4]+"\t"+ s_mal[0]+  QString("\t%1B").arg(dw2float(&data[105+j*8]),0,'f',3) +   "\r\n";
                }else{
                    res += DUTs[j*4]+"\t"+ s_mal[0] +  QString("\t%1B").arg(dw2float(&data[105+j*8]),0,'f',3) +   "\r\n";
                    res += DUTs[j*4+1]+"\t"+ s_mal[1]+ QString("\t%1B").arg(dw2float(&data[105+j*8+2]),0,'f',3) +"\r\n";
                    res += DUTs[j*4+2]+"\t"+ s_mal[2]+  QString("\t%1B").arg(dw2float(&data[105+j*8+4]),0,'f',3) +"\r\n";
                    res += DUTs[j*4+3]+"\t"+ s_mal[3]+   QString("\t%1B").arg(dw2float(&data[105+j*8+6]),0,'f',3) +"\r\n";
                }
            }

            res+="\n";
        }
    }

    return res;
}

void OpenShortTest::AnalyzeMalFunction(uint16_t data, QString* s_mal)
{
    uint8_t m_cmp;
    uint8_t m_lat;
    uint8_t cmp[4];
    uint8_t latch[4];
    m_cmp = (data&0xFF00)>>8;
    m_lat = (data&0xFF);
    const int Mask_CMP=0x03;
    for(uint8_t i=0;i<4;i++)
    {
        cmp[i] = (m_cmp&(Mask_CMP<<(2*i)))>>(2*i);
        latch[i] = (m_lat&(Mask_CMP<<(2*i)))>>(2*i);

        if(cmp[i]==3){//CMP_L=1 CMP_H=1
            s_mal[i] = "Ok";
        }else if (cmp[i]==2){//CMP_L=1 CMP_H=0
            if(Pos_neg){
                s_mal[i] = "Open";
            }else{
                s_mal[i] = "Short";
            }

        }else if(cmp[i]==1){//CMP_L=0 CMP_H=1
            if(Pos_neg){
                s_mal[i] = "Short";
            }else{
                s_mal[i] = "Open";
            }
        }else{//CMP_L=0 CMP_H=0
            s_mal[i] = "Undefined";
        }

        if(latch[i]==2){
            s_mal[i]+="\tc=0\t   ";
        }else if (latch[i]==1){
            s_mal[i]+="\tLc=0\t   ";
        }else if(latch[i]==0){
            s_mal[i]+="\tLc=0\tc=0";
        }else{
            s_mal[i]+="\t   \t   ";
        }

    }
}

QList<SigMal>* OpenShortTest::ParseLogFile(QString pathfile)
{
    QFile f;
    QList<SigMal>* res = new QList<SigMal>();

    f.setFileName(pathfile);
    QTextStream in(&f);
    if(f.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString line;
        QStringList terms;
        SigMal elem;
        do{
            line = in.readLine();
            if(line.contains("MKM")){
                continue;
            }
            terms = line.split("\t");
            if(terms.size()>=2){
                elem.name = terms[0];
                elem.mal = terms[1];
                res->append(elem);
            }
        }while(!line.isEmpty());

    }else{
        return NULL;
    }

    f.close();
    return res;
}
