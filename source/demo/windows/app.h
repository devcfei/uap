#ifndef _APP_H_
#define _APP_H_


using namespace uap;

class App
{
public:
    App();
    ~App();


    Result createApplication();
    Result initApplication();

    Result startUI();
    Result setLayout();

private:

    sptr<IApplication> spApp_;

    sptr<IUiEngine> spUiEngine_;
    sptr<IAttributes> spUiAttributes_;


    sptr<IUiLayout> spLayout_;
    sptr<IAttributes> spLayoutAttributes_;


    Result buildLayout();

};




#endif //@_APP_H_