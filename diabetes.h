//
// Created by Brian Clauser on 2018-12-06.
//

#ifndef DIABETES_DETECTION_DIABETES_H
#define DIABETES_DETECTION_DIABETES_H


class diabetes {
private:
    char name[40];
    float age;
    float ht;
    int wt;
    char sex;
    char *s;

public:
    void welcome_screen(void);
    void getvalue(void);
    void getlevel1_symptoms(void);
    void getlevel2_symptoms(void);
    void getlevel3_symptoms(void);
    int analyse_symptoms(int);
    char display_message(int, int);
    bool init();
    bool loadAudio();
    void close();

};


#endif //DIABETES_DETECTION_DIABETES_H
