#ifndef COUP_H
#define COUP_H

class Coup
{
    private : 
        bool coup_droit;
        bool revers;
        float puissance;
        float precision;

    public :
        Coup();
        
        Coup(bool c, bool r, float puis, float prec);

        ~Coup();

        bool getCoupDroit();

        bool getRevers();

        float getPuissance();

        float getPrecision();

        void setCoupDroit(bool c);

        void setRevers(bool r);

        void setPuissance(float p);

        void setPrecision(float p);

        void AugmenterDiminuerPuissance(float p);

        void AugmenterDiminuerPrecision(float p);


};


#endif