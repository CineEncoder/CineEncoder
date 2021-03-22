#include "preset.h"
#include "ui_preset.h"



Preset::Preset(QWidget *parent) :
    QDialog(parent),
    ui_preset(new Ui::Preset)
{
    ui_preset->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::SubWindow);
    this->setMouseTracking(true);
}

Preset::~Preset()
{
    delete ui_preset;
}

void Preset::on_pushButton_7_clicked()  //********************************************* Close preset window ****************//
{
    this->close();
}

void Preset::on_closeWindow_2_clicked()
{
    this->close();
}

void Preset::on_expandWindow_2_clicked()
{
    if (_expandWindowsState == false)
    {
        this->showMaximized();
        _expandWindowsState = true;
        QIcon iconShowMax;
        iconShowMax.addFile(QString::fromUtf8(":/resources/icons/16x16/cil-clone.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui_preset->expandWindow_2->setIcon(iconShowMax);
    } else {
        this->showNormal();
        _expandWindowsState = false;
        QIcon iconShowNorm;
        iconShowNorm.addFile(QString::fromUtf8(":/resources/icons/16x16/cil-media-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        ui_preset->expandWindow_2->setIcon(iconShowNorm);
    }
}

void Preset::on_hideWindow_2_clicked()
{
    this->showMinimized();
}

void Preset::setParameters()  //********************************************************* Set parameters *******************//
{
    ui_preset->frame_hint->installEventFilter(this);
    ui_preset->widget->installEventFilter(this);
    ui_preset->widget->setAttribute(Qt::WA_Hover, true);
    mouseClickCoordinate.setX(0);
    mouseClickCoordinate.setY(0);
    _repeat = 0;
    timer = new QTimer(this);
    timer->setInterval(450);
    connect(timer, SIGNAL(timeout()), this, SLOT(repeat_handler()));
    timer->start();
    ui_preset->lineEdit_presetname->setText(_cur_param[curParamIndex::PRESET_NAME]);
    if (_cur_param[curParamIndex::PRESET_NAME] != "New preset") {
        ui_preset->comboBox_codec->setCurrentIndex(_cur_param[CODEC].toInt());
        ui_preset->comboBox_mode->setCurrentIndex(_cur_param[MODE].toInt());
        ui_preset->comboBox_container->setCurrentIndex(_cur_param[CONTAINER].toInt());
        ui_preset->comboBox_bitrate->setCurrentText(_cur_param[BQR]);
        ui_preset->comboBox_maxrate->setCurrentText(_cur_param[MAXRATE]);
        ui_preset->comboBox_bufsize->setCurrentText(_cur_param[BUFSIZE]);
        ui_preset->checkBox_2->setEnabled(bool(_cur_param[RESIZE_ENABLED].toUShort()));
        ui_preset->checkBox_2->setChecked(_cur_param[RESIZE_CHECKSTATE].toInt());
        ui_preset->comboBox_width->setCurrentText(_cur_param[WIDTH]);
        ui_preset->comboBox_height->setCurrentText(_cur_param[HEIGHT]);
        ui_preset->comboBox_pass->setCurrentIndex(_cur_param[PASS].toInt());
        ui_preset->comboBox_preset->setCurrentIndex(_cur_param[PRESET].toInt());
        ui_preset->comboBox_color_range->setCurrentIndex(_cur_param[COLOR_RANGE].toInt());
        ui_preset->lineEdit_min_lum->setText(_cur_param[MIN_LUM]);
        ui_preset->lineEdit_max_lum->setText(_cur_param[MAX_LUM]);
        ui_preset->lineEdit_max_cll->setText(_cur_param[MAX_CLL]);
        ui_preset->lineEdit_max_fall->setText(_cur_param[MAX_FALL]);
        ui_preset->comboBox_master_disp->setCurrentIndex(_cur_param[MASTER_DISPLAY].toInt());
        ui_preset->lineEdit_chroma_coord->setText(_cur_param[CHROMA_COORD]);
        ui_preset->lineEdit_white_coord->setText(_cur_param[WHITE_COORD]);
        ui_preset->comboBox_audio_codec->setCurrentIndex(_cur_param[AUDIO_CODEC].toInt());
        ui_preset->comboBox_audio_bitrate->setCurrentIndex(_cur_param[AUDIO_BITRATE].toInt());
    }
}

void Preset::on_comboBox_codec_currentTextChanged(const QString &arg1)  //************* Change current codec ***************//
{
    std::cout << "Change current codec..." << std::endl;
    ui_preset->checkBox_2->setEnabled(true);
    ui_preset->comboBox_container->setEnabled(true);
    ui_preset->comboBox_mode->setEnabled(true);
    ui_preset->comboBox_pass->setEnabled(true);
    ui_preset->comboBox_preset->setEnabled(true);
    ui_preset->comboBox_color_range->setEnabled(true);
    ui_preset->lineEdit_min_lum->setEnabled(true);
    ui_preset->lineEdit_max_lum->setEnabled(true);
    ui_preset->lineEdit_max_cll->setEnabled(true);
    ui_preset->lineEdit_max_fall->setEnabled(true);
    ui_preset->comboBox_master_disp->setEnabled(true);
    ui_preset->comboBox_container->clear();
    ui_preset->comboBox_mode->clear();
    ui_preset->comboBox_pass->clear();
    ui_preset->comboBox_preset->clear();
    ui_preset->comboBox_audio_codec->clear();
    if (arg1 == "H.265/HEVC 4:2:0 10 bit") {
        ui_preset->comboBox_container->addItems({"MKV", "MOV", "MP4"});
        ui_preset->comboBox_container->setCurrentIndex(2);
        ui_preset->comboBox_mode->addItems({"Constant Bitrate", "Average Bitrate", "Variable Bitrate", "Constant Rate Factor", "Constant QP"});
        ui_preset->comboBox_pass->addItems({"1 Pass", "2 Pass"});
        ui_preset->comboBox_profile->setCurrentIndex(MAIN10);
        ui_preset->comboBox_preset->addItems({"Ultrafast", "Superfast", "Veryfast", "Faster", "Fast", "Medium", "Slow", "Slower", "Veryslow"});
        ui_preset->comboBox_preset->setCurrentIndex(6);
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV420P10LE);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "From source"});
    }
    if (arg1 == "H.265/HEVC 4:2:0 8 bit") {
        ui_preset->comboBox_container->addItems({"MKV", "MOV", "MP4", "M2TS", "TS"});
        ui_preset->comboBox_container->setCurrentIndex(2);
        ui_preset->comboBox_mode->addItems({"Constant Bitrate", "Average Bitrate", "Variable Bitrate", "Constant Rate Factor", "Constant QP"});
        ui_preset->comboBox_pass->addItems({"1 Pass", "2 Pass"});
        ui_preset->comboBox_profile->setCurrentIndex(MAIN);
        ui_preset->comboBox_preset->addItems({"Ultrafast", "Superfast", "Veryfast", "Faster", "Fast", "Medium", "Slow", "Slower", "Veryslow"});
        ui_preset->comboBox_preset->setCurrentIndex(6);
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV420P);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "From source"});
    }
    if (arg1 == "H.264/AVC 4:2:0 8 bit") {
        ui_preset->comboBox_container->addItems({"MKV", "MOV", "MP4", "M2TS", "TS"});
        ui_preset->comboBox_container->setCurrentIndex(2);
        ui_preset->comboBox_mode->addItems({"Constant Bitrate", "Average Bitrate", "Variable Bitrate", "Constant Rate Factor", "Constant QP"});
        ui_preset->comboBox_pass->addItems({"1 Pass", "2 Pass"});
        ui_preset->comboBox_profile->setCurrentIndex(HIGH);
        ui_preset->comboBox_preset->addItems({"Ultrafast", "Superfast", "Veryfast", "Faster", "Fast", "Medium", "Slow", "Slower", "Veryslow"});
        ui_preset->comboBox_preset->setCurrentIndex(6);
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV420P);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "From source"});
    }
    if (arg1 == "Intel QSV H.264/AVC 4:2:0 8 bit") {
        ui_preset->checkBox_2->setChecked(false);
        ui_preset->checkBox_2->setEnabled(false);
        ui_preset->comboBox_container->addItems({"MKV", "MOV", "MP4"});
        ui_preset->comboBox_container->setCurrentIndex(2);
        ui_preset->comboBox_mode->addItems({"Variable Bitrate"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(Profile::HIGH);
        ui_preset->comboBox_preset->addItems({"Veryfast", "Faster", "Fast", "Medium", "Slow", "Slower", "Veryslow"});
        ui_preset->comboBox_preset->setCurrentIndex(4);
        ui_preset->comboBox_pixfmt->setCurrentIndex(Pixformat::PIXFORMAT_AUTO);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "From source"});
    }
    if (arg1 == "Intel QSV MPEG-2 4:2:0 8 bit") {
        ui_preset->checkBox_2->setChecked(false);
        ui_preset->checkBox_2->setEnabled(false);
        ui_preset->comboBox_container->addItems({"MKV", "MPG", "AVI", "M2TS", "TS"});
        ui_preset->comboBox_container->setCurrentIndex(3);
        ui_preset->comboBox_mode->addItems({"Constant Bitrate"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(Profile::HIGH);
        ui_preset->comboBox_preset->addItems({"Veryfast", "Faster", "Fast", "Medium", "Slow", "Slower", "Veryslow"});
        ui_preset->comboBox_preset->setCurrentIndex(4);
        ui_preset->comboBox_pixfmt->setCurrentIndex(Pixformat::YUV420P);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "From source"});
    }
    if (arg1 == "NVENC H.265/HEVC 4:2:0 10 bit") {
        ui_preset->comboBox_container->addItems({"MKV", "MOV", "MP4"});
        ui_preset->comboBox_container->setCurrentIndex(2);
        ui_preset->comboBox_mode->addItems({"Variable Bitrate"});
        ui_preset->comboBox_pass->addItems({"2 Pass Optimisation"});
        ui_preset->comboBox_profile->setCurrentIndex(MAIN10);
        ui_preset->comboBox_preset->addItems({"Slow"});
        //ui_preset->comboBox_preset->setCurrentIndex(6);
        ui_preset->comboBox_pixfmt->setCurrentIndex(P010LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "From source"});
    }
    if (arg1 == "NVENC H.265/HEVC 4:2:0 8 bit") {
        ui_preset->comboBox_container->addItems({"MKV", "MOV", "MP4", "M2TS", "TS"});
        ui_preset->comboBox_container->setCurrentIndex(2);
        ui_preset->comboBox_mode->addItems({"Variable Bitrate"});
        ui_preset->comboBox_pass->addItems({"2 Pass Optimisation"});
        ui_preset->comboBox_profile->setCurrentIndex(MAIN);
        ui_preset->comboBox_preset->addItems({"Slow"});
        //ui_preset->comboBox_preset->setCurrentIndex(6);
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV420P);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "From source"});
    }
    if (arg1 == "NVENC H.264/AVC 4:2:0 8 bit") {
        ui_preset->comboBox_container->addItems({"MKV", "MOV", "MP4", "M2TS", "TS"});
        ui_preset->comboBox_container->setCurrentIndex(2);
        ui_preset->comboBox_mode->addItems({"Variable Bitrate"});
        ui_preset->comboBox_pass->addItems({"2 Pass Optimisation"});
        ui_preset->comboBox_profile->setCurrentIndex(HIGH);
        ui_preset->comboBox_preset->addItems({"Slow"});
        //ui_preset->comboBox_preset->setCurrentIndex(6);
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV420P);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "From source"});
    }
    if (arg1 == "VP9 4:2:0 10 bit") {
        ui_preset->comboBox_container->addItems({"WebM", "MKV"});
        ui_preset->comboBox_mode->addItems({"Average Bitrate", "Constant Rate Factor"});
        ui_preset->comboBox_pass->addItems({"1 Pass", "2 Pass"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_2);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV420P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"Opus", "Vorbis", "From source"});
    }
    if (arg1 == "VP9 4:2:0 8 bit") {
        ui_preset->comboBox_container->addItems({"WebM", "MKV"});
        ui_preset->comboBox_mode->addItems({"Average Bitrate", "Constant Rate Factor"});
        ui_preset->comboBox_pass->addItems({"1 Pass", "2 Pass"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_1);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV420P);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"Opus", "Vorbis", "From source"});
    }
    if (arg1 == "ProRes Proxy") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_0);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV422P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "ProRes LT") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_1);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV422P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "ProRes Standard") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_2);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV422P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "ProRes HQ") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_3);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV422P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "ProRes 4444") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_4);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV444P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "ProRes 4444 XQ") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_5);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV444P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "DNxHR LB") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(DNXHR_LB);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV422p);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "DNxHR SQ") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(DNXHR_SQ);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV422p);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "DNxHR HQ") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(DNXHR_HQ);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV422p);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "DNxHR HQX") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(DNXHR_HQX);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV422P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "DNxHR 444") {
        ui_preset->comboBox_container->addItems({"MOV"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(DNXHR_444);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(YUV444P10LE);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit", "PCM 24 bit", "PCM 32 bit"});
    }
    if (arg1 == "XDCAM HD422") {
        ui_preset->comboBox_container->addItems({"MXF"});
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(Profile::PROFILE_AUTO);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(Pixformat::YUV422p);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_container->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_color_range->setCurrentIndex(0);
        ui_preset->lineEdit_min_lum->clear();
        ui_preset->lineEdit_max_lum->clear();
        ui_preset->lineEdit_max_cll->clear();
        ui_preset->lineEdit_max_fall->clear();
        ui_preset->comboBox_master_disp->setCurrentIndex(0);
        ui_preset->comboBox_color_range->setEnabled(false);
        ui_preset->lineEdit_min_lum->setEnabled(false);
        ui_preset->lineEdit_max_lum->setEnabled(false);
        ui_preset->lineEdit_max_cll->setEnabled(false);
        ui_preset->lineEdit_max_fall->setEnabled(false);
        ui_preset->comboBox_master_disp->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"PCM 16 bit"});
    }
    if (arg1 == "From source") {
        ui_preset->checkBox_2->setChecked(false);
        ui_preset->checkBox_2->setEnabled(false);
        ui_preset->comboBox_container->addItems({"MKV", "MOV", "MP4", "M2TS", "TS"});
        ui_preset->comboBox_container->setCurrentIndex(2);
        ui_preset->comboBox_mode->addItems({"Auto"});
        ui_preset->comboBox_pass->addItems({"Auto"});
        ui_preset->comboBox_profile->setCurrentIndex(PROFILE_AUTO);
        ui_preset->comboBox_preset->addItems({"Auto"});
        ui_preset->comboBox_pixfmt->setCurrentIndex(PIXFORMAT_AUTO);
        ui_preset->comboBox_preset->setEnabled(false);
        ui_preset->comboBox_mode->setEnabled(false);
        ui_preset->comboBox_pass->setEnabled(false);
        ui_preset->comboBox_audio_codec->addItems({"AAC", "AC3", "DTS", "Vorbis", "Opus", "From source"});
    }
}

void Preset::on_checkBox_2_stateChanged(int arg1)  //************************************* Enable resize *******************//
{
    std::cout << "Change state resize..." << std::endl;
    if (arg1 == 2) {
        ui_preset->comboBox_width->setEnabled(true);
        ui_preset->comboBox_height->setEnabled(true);
    } else {
        ui_preset->comboBox_width->clearEditText();
        ui_preset->comboBox_height->clearEditText();
        ui_preset->comboBox_width->clear();
        ui_preset->comboBox_height->clear();
        ui_preset->comboBox_width->addItems({"Source"});
        ui_preset->comboBox_height->addItems({"Source"});
        ui_preset->comboBox_width->setEnabled(false);
        ui_preset->comboBox_height->setEnabled(false);
    };
    _repeat++;
}

void Preset::on_comboBox_mode_currentTextChanged(const QString &arg1)  //*************** Change curret mode ****************//
{
    std::cout << "Change current mode..." << std::endl;
    ui_preset->comboBox_bitrate->setEnabled(true);
    ui_preset->comboBox_maxrate->setEnabled(true);
    ui_preset->comboBox_bufsize->setEnabled(true);
    ui_preset->comboBox_bitrate->clear();
    ui_preset->comboBox_maxrate->clear();
    ui_preset->comboBox_bufsize->clear();
    if (arg1 == "Auto") {
        ui_preset->label_bitrate->setText("Bitrate");
        ui_preset->label_maxrate->setText("Maxrate");
        ui_preset->label_bufsize->setText("Bufsize");
        ui_preset->label_maxrate->show();
        ui_preset->label_bufsize->show();
        ui_preset->comboBox_maxrate->show();
        ui_preset->comboBox_bufsize->show();
        ui_preset->comboBox_bitrate->addItems({"Auto"});
        ui_preset->comboBox_maxrate->addItems({"Auto"});
        ui_preset->comboBox_bufsize->addItems({"Auto"});
        ui_preset->comboBox_bitrate->setEnabled(false);
        ui_preset->comboBox_maxrate->setEnabled(false);
        ui_preset->comboBox_bufsize->setEnabled(false);
    };
    if (arg1 == "Constant Bitrate") {
        ui_preset->label_bitrate->setText("Bitrate");
        ui_preset->label_maxrate->hide();
        ui_preset->label_bufsize->hide();
        ui_preset->comboBox_maxrate->hide();
        ui_preset->comboBox_bufsize->hide();
        ui_preset->comboBox_bitrate->addItems({"65M", "60M", "55M", "50M", "40M", "30M", "20M", "10M", "5M"});
        ui_preset->comboBox_bitrate->setCurrentIndex(3);
    };
    if (arg1 == "Average Bitrate") {
        ui_preset->label_bitrate->setText("Bitrate");
        ui_preset->label_maxrate->hide();
        ui_preset->label_bufsize->hide();
        ui_preset->comboBox_maxrate->hide();
        ui_preset->comboBox_bufsize->hide();
        ui_preset->comboBox_bitrate->addItems({"65M", "60M", "55M", "50M", "40M", "30M", "20M", "10M", "5M"});
        ui_preset->comboBox_bitrate->setCurrentIndex(3);
    };
    if (arg1 == "Variable Bitrate") {
        ui_preset->label_bitrate->setText("Bitrate");
        ui_preset->label_maxrate->setText("Maxrate");
        ui_preset->label_bufsize->setText("Bufsize");
        ui_preset->label_maxrate->show();
        ui_preset->label_bufsize->show();
        ui_preset->comboBox_maxrate->show();
        ui_preset->comboBox_bufsize->show();
        ui_preset->comboBox_bitrate->addItems({"65M", "60M", "55M", "50M", "40M", "30M", "20M", "10M", "5M"});
        ui_preset->comboBox_maxrate->addItems({"65M", "60M", "55M", "50M", "40M", "30M", "20M", "10M", "5M"});
        ui_preset->comboBox_bufsize->addItems({"65M", "60M", "55M", "50M", "40M", "30M", "20M", "10M", "5M"});
        ui_preset->comboBox_bitrate->setCurrentIndex(3);
        ui_preset->comboBox_maxrate->setCurrentIndex(3);
        ui_preset->comboBox_bufsize->setCurrentIndex(3);
    };
    if (arg1 == "Constant Rate Factor") {
        ui_preset->label_bitrate->setText("Rate factor");
        ui_preset->label_maxrate->hide();
        ui_preset->label_bufsize->hide();
        ui_preset->comboBox_maxrate->hide();
        ui_preset->comboBox_bufsize->hide();
        ui_preset->comboBox_bitrate->addItems({"51", "45", "40", "35", "30", "25", "24", "23", "22", "21", "20",
                                               "19", "18", "17", "16", "15", "10", "5", "1"});
        ui_preset->comboBox_bitrate->setCurrentIndex(10);
    };
    if (arg1 == "Constant QP") {
        ui_preset->label_bitrate->setText("Quantizer");
        ui_preset->label_maxrate->hide();
        ui_preset->label_bufsize->hide();
        ui_preset->comboBox_maxrate->hide();
        ui_preset->comboBox_bufsize->hide();
        ui_preset->comboBox_bitrate->addItems({"51", "45", "40", "35", "30", "25", "24", "23", "22", "21", "20",
                                               "19", "18", "17", "16", "15", "10", "5", "1"});
        ui_preset->comboBox_bitrate->setCurrentIndex(10);
    };
}

void Preset::on_comboBox_audio_codec_currentTextChanged(const QString &arg1) //***** Change current audio codec ************//
{
    std::cout << "Change current audio codec..." << std::endl;
    ui_preset->comboBox_audio_bitrate->setEnabled(true);
    ui_preset->comboBox_audio_bitrate->clear();
    if (arg1 == "From source") {
        ui_preset->comboBox_audio_bitrate->addItems({"From source"});
        ui_preset->comboBox_audio_bitrate->setEnabled(false);
    };
    if (arg1 == "AAC") {
        ui_preset->comboBox_audio_bitrate->addItems({"384k", "320k", "256k", "192k", "128k", "96k"});
        ui_preset->comboBox_audio_bitrate->setCurrentIndex(2);
    };
    if (arg1 == "AC3") {
        ui_preset->comboBox_audio_bitrate->addItems({"640k", "448k", "384k", "256k"});
        ui_preset->comboBox_audio_bitrate->setCurrentIndex(1);
    };
    if (arg1 == "DTS") {
        ui_preset->comboBox_audio_bitrate->addItems({"3840k", "3072k", "2048k", "1920k", "1536k", "1472k", "1344k", "1280k", "1152k",
                                                     "1024k", "960k", "768k", "640k", "576k", "512k", "448k", "384k"});
        ui_preset->comboBox_audio_bitrate->setCurrentIndex(4);
    };
    if (arg1 == "Vorbis") {
        ui_preset->comboBox_audio_bitrate->addItems({"448k", "384k", "256k", "128k", "96k", "64k"});
        ui_preset->comboBox_audio_bitrate->setCurrentIndex(2);
    };
    if (arg1 == "Opus") {
        ui_preset->comboBox_audio_bitrate->addItems({"448k", "384k", "256k", "128k", "96k", "64k"});
        ui_preset->comboBox_audio_bitrate->setCurrentIndex(2);
    };
    if (arg1 == "PCM 16 bit") {
        ui_preset->comboBox_audio_bitrate->addItems({"Auto"});
        ui_preset->comboBox_audio_bitrate->setEnabled(false);
    };
    if (arg1 == "PCM 24 bit") {
        ui_preset->comboBox_audio_bitrate->addItems({"Auto"});
        ui_preset->comboBox_audio_bitrate->setEnabled(false);
    };
    if (arg1 == "PCM 32 bit") {
        ui_preset->comboBox_audio_bitrate->addItems({"Auto"});
        ui_preset->comboBox_audio_bitrate->setEnabled(false);
    };
    _repeat++;
}

void Preset::on_comboBox_master_disp_currentTextChanged(const QString &arg1)  //*** Change current master display **********//
{
    std::cout << "Change current master display..." << std::endl;
    ui_preset->lineEdit_chroma_coord->clear();
    ui_preset->lineEdit_white_coord->clear();
    ui_preset->lineEdit_chroma_coord->setEnabled(true);
    ui_preset->lineEdit_white_coord->setEnabled(true);
    if (arg1 == "Unsprt") {
        ui_preset->lineEdit_chroma_coord->setText("Unsprt");
        ui_preset->lineEdit_white_coord->setText("Unsprt");
        ui_preset->lineEdit_chroma_coord->setEnabled(false);
        ui_preset->lineEdit_white_coord->setEnabled(false);
    };
    if (arg1 == "From source") {
        ui_preset->lineEdit_chroma_coord->setText("From source");
        ui_preset->lineEdit_white_coord->setText("From source");
        ui_preset->lineEdit_chroma_coord->setEnabled(false);
        ui_preset->lineEdit_white_coord->setEnabled(false);
    };
    if (arg1 == "Custom") {
        ui_preset->lineEdit_chroma_coord->setText("0.680,0.320,0.265,0.690,0.150,0.060");
        ui_preset->lineEdit_white_coord->setText("0.3127,0.3290");
    };
    if (arg1 == "Display P3") {
        ui_preset->lineEdit_chroma_coord->setText("0.680,0.320,0.265,0.690,0.150,0.060");
        ui_preset->lineEdit_white_coord->setText("0.3127,0.3290");
        ui_preset->lineEdit_chroma_coord->setEnabled(false);
        ui_preset->lineEdit_white_coord->setEnabled(false);
    };
    if (arg1 == "DCI P3") {
        ui_preset->lineEdit_chroma_coord->setText("0.680,0.320,0.265,0.690,0.150,0.060");
        ui_preset->lineEdit_white_coord->setText("0.314,0.3510");
        ui_preset->lineEdit_chroma_coord->setEnabled(false);
        ui_preset->lineEdit_white_coord->setEnabled(false);
    };
    if (arg1 == "BT.2020") {
        ui_preset->lineEdit_chroma_coord->setText("0.708,0.292,0.170,0.797,0.131,0.046");
        ui_preset->lineEdit_white_coord->setText("0.3127,0.3290");
        ui_preset->lineEdit_chroma_coord->setEnabled(false);
        ui_preset->lineEdit_white_coord->setEnabled(false);
    };
    if (arg1 == "BT.709") {
        ui_preset->lineEdit_chroma_coord->setText("0.640,0.330,0.30,0.60,0.150,0.060");
        ui_preset->lineEdit_white_coord->setText("0.3127,0.3290");
        ui_preset->lineEdit_chroma_coord->setEnabled(false);
        ui_preset->lineEdit_white_coord->setEnabled(false);
    };
}

void Preset::on_pushButton_6_clicked()  //************************************************* Apply preset *******************//
{
    _cur_param[PRESET_NAME] = ui_preset->lineEdit_presetname->text();
    _cur_param[CODEC] = QString::number(ui_preset->comboBox_codec->currentIndex());
    _cur_param[MODE] = QString::number(ui_preset->comboBox_mode->currentIndex());
    _cur_param[CONTAINER] = QString::number(ui_preset->comboBox_container->currentIndex());
    _cur_param[BQR] = ui_preset->comboBox_bitrate->currentText();
    _cur_param[MAXRATE] = ui_preset->comboBox_maxrate->currentText();
    _cur_param[BUFSIZE] = ui_preset->comboBox_bufsize->currentText();
    _cur_param[RESIZE_ENABLED] = QString::number(int(ui_preset->checkBox_2->isEnabled()));
    _cur_param[RESIZE_CHECKSTATE] = QString::number(ui_preset->checkBox_2->checkState());
    _cur_param[WIDTH] = ui_preset->comboBox_width->currentText();
    _cur_param[HEIGHT] = ui_preset->comboBox_height->currentText();
    _cur_param[PASS]= QString::number(ui_preset->comboBox_pass->currentIndex());
    _cur_param[PRESET] = QString::number(ui_preset->comboBox_preset->currentIndex());
    _cur_param[COLOR_RANGE] = QString::number(ui_preset->comboBox_color_range->currentIndex());
    _cur_param[MIN_LUM] = ui_preset->lineEdit_min_lum->text();
    _cur_param[MAX_LUM] = ui_preset->lineEdit_max_lum->text();
    _cur_param[MAX_CLL] = ui_preset->lineEdit_max_cll->text();
    _cur_param[MAX_FALL] = ui_preset->lineEdit_max_fall->text();
    _cur_param[MASTER_DISPLAY] = QString::number(ui_preset->comboBox_master_disp->currentIndex());
    _cur_param[CHROMA_COORD] = ui_preset->lineEdit_chroma_coord->text();
    _cur_param[WHITE_COORD] = ui_preset->lineEdit_white_coord->text();
    _cur_param[AUDIO_CODEC] = QString::number(ui_preset->comboBox_audio_codec->currentIndex());
    _cur_param[AUDIO_BITRATE] = QString::number(ui_preset->comboBox_audio_bitrate->currentIndex());
    this->close();
}

void Preset::change_preset_name()  //************************************************ Call Change preset name **************//
{
    std::cout << "Call change preset name..." << std::endl;
    int c1 = ui_preset->comboBox_codec->currentIndex();
    int c2 = ui_preset->comboBox_mode->currentIndex();
    int c11 = ui_preset->comboBox_pass->currentIndex();
    int c12 = ui_preset->comboBox_preset->currentIndex();
    int c21 = ui_preset->comboBox_audio_codec->currentIndex();
    int c22 = ui_preset->comboBox_audio_bitrate->currentIndex();
    QString w = ui_preset->comboBox_width->currentText();
    QString h = ui_preset->comboBox_height->currentText();
    QString container = ui_preset->comboBox_container->currentText();
    QString codec, res, mode, clrspace, preset, pass, hdr, acodec, abitrate;
    QString fps = "Fps: Source, ";
    if ((c1 == -1) || (c2 == -1)) {
        return;
    }
    if ((c11 == -1) || (c12 == -1)) {
        return;
    }
    if ((c21 == -1) || (c22 == -1)) {
        return;
    }
    QString arr_codec[NUMBER_PRESETS][3] = {
        {"HEVC, ",             "YUV, 4:2:0, 10 bit, ", "HDR: "},
        {"HEVC, ",             "YUV, 4:2:0, 8 bit, ",  ""},
        {"AVC, ",              "YUV, 4:2:0, 8 bit, ",  ""},
        {"Intel QSV, AVC, ",   "YUV, 4:2:0, 8 bit, ",  ""},
        {"Intel QSV, MPEG-2, ","YUV, 4:2:0, 8 bit, ",  ""},
        {"NVENC, HEVC, ",      "YUV, 4:2:0, 10 bit, ", "HDR: "},
        {"NVENC, HEVC, ",      "YUV, 4:2:0, 8 bit, ",  ""},
        {"NVENC, AVC, ",       "YUV, 4:2:0, 8 bit, ",  ""},
        {"VP9, ",              "YUV, 4:2:0, 10 bit, ", "HDR: "},
        {"VP9, ",              "YUV, 4:2:0, 8  bit, ", ""},
        {"ProRes Proxy, ",     "YUV, 4:2:2, 10 bit, ", "HDR: "},
        {"ProRes LT, ",        "YUV, 4:2:2, 10 bit, ", "HDR: "},
        {"ProRes Standard, ",  "YUV, 4:2:2, 10 bit, ", "HDR: "},
        {"ProRes HQ, ",        "YUV, 4:2:2, 10 bit, ", "HDR: "},
        {"ProRes 4444, ",      "YUV, 4:4:4, 10 bit, ", "HDR: "},
        {"ProRes 4444XQ, ",    "YUV, 4:4:4, 10 bit, ", "HDR: "},
        {"DNxHR LB, ",         "YUV, 4:2:2, 8 bit, ",  ""},
        {"DNxHR SQ, ",         "YUV, 4:2:2, 8 bit, ",  ""},
        {"DNxHR HQ, ",         "YUV, 4:2:2, 8 bit, ",  ""},
        {"DNxHR HQX, ",        "YUV, 4:2:2, 10 bit, ", "HDR: "},
        {"DNxHR 444, ",        "YUV, 4:4:4, 10 bit, ", "HDR: "},
        {"XDCAM HD422, ",      "YUV, 4:2:2, 8 bit, ",  ""},
        {"From source, ",      "",                     "HDR: "}
    };
    codec = arr_codec[c1][0];
    clrspace = arr_codec[c1][1];
    if (w == "" or h == "") {
        res = "Res: Source, ";
    } else if (w == "Source" or h == "Source") {
        res = "Res: Source, ";
    } else if (w != "Source" && h != "Source") {
        res = "Res: " + w + "x" + h + ", ";
    }
    QString arr_mode[NUMBER_PRESETS][5] = {
        {"CBR", "ABR", "VBR", "CRF", "CQP"},
        {"CBR", "ABR", "VBR", "CRF", "CQP"},
        {"CBR", "ABR", "VBR", "CRF", "CQP"},
        {"VBR", "",    "",    "",    ""},
        {"CBR", "",    "",    "",    ""},
        {"VBR", "",    "",    "",    ""},
        {"VBR", "",    "",    "",    ""},
        {"VBR", "",    "",    "",    ""},
        {"ABR", "CRF", "",    "",    ""},
        {"ABR", "CRF", "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""},
        {"",    "",    "",    "",    ""}
    };
    if (arr_mode[c1][c2] != "") {
        mode = arr_mode[c1][c2] + " " + ui_preset->comboBox_bitrate->currentText() + ", ";
    }
    QString arr_preset[NUMBER_PRESETS][9] = {
        {"Ultrafast", "Superfast", "Veryfast", "Faster", "Fast", "Medium", "Slow",     "Slower", "Veryslow"},
        {"Ultrafast", "Superfast", "Veryfast", "Faster", "Fast", "Medium", "Slow",     "Slower", "Veryslow"},
        {"Ultrafast", "Superfast", "Veryfast", "Faster", "Fast", "Medium", "Slow",     "Slower", "Veryslow"},
        {"Veryfast",  "Faster",    "Fast",     "Medium", "Slow", "Slower", "Veryslow", "",       ""},
        {"Veryfast",  "Faster",    "Fast",     "Medium", "Slow", "Slower", "Veryslow", "",       ""},
        {"Slow",      "",          "",         "",       "",     "",       "",         "",       ""},
        {"Slow",      "",          "",         "",       "",     "",       "",         "",       ""},
        {"Slow",      "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""},
        {"",          "",          "",         "",       "",     "",       "",         "",       ""}
    };
    if (arr_preset[c1][c12] != "") {
        preset = "Preset: " + arr_preset[c1][c12] + ", ";
    }
    QString arr_pass[NUMBER_PRESETS][2] = {
        {"1 Pass", "2 Pass"},
        {"1 Pass", "2 Pass"},
        {"1 Pass", "2 Pass"},
        {"",       ""},
        {"",       ""},
        {"2 Pass", ""},
        {"2 Pass", ""},
        {"2 Pass", ""},
        {"1 Pass", "2 Pass"},
        {"1 Pass", "2 Pass"},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""},
        {"",       ""}
    };
    if (arr_pass[c1][c11] != "") {
        pass = arr_pass[c1][c11] + ", ";
    }
    if (arr_codec[c1][2] != "") {
        hdr = arr_codec[c1][2] + "Enabled, ";
    }
    QString arr_acodec[NUMBER_PRESETS][6] = {
        {"AAC",        "AC3",        "DTS",        "Source", "",     ""},
        {"AAC",        "AC3",        "DTS",        "Source", "",     ""},
        {"AAC",        "AC3",        "DTS",        "Source", "",     ""},
        {"AAC",        "AC3",        "DTS",        "Source", "",     ""},
        {"AAC",        "AC3",        "DTS",        "Source", "",     ""},
        {"AAC",        "AC3",        "DTS",        "Source", "",     ""},
        {"AAC",        "AC3",        "DTS",        "Source", "",     ""},
        {"AAC",        "AC3",        "DTS",        "Source", "",     ""},
        {"Opus",       "Vorbis",     "Source",     "",       "",     ""},
        {"Opus",       "Vorbis",     "Source",     "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "PCM 24 bit", "PCM 32 bit", "",       "",     ""},
        {"PCM 16 bit", "",           "",           "",       "",     ""},
        {"AAC",        "AC3",        "DTS",        "Vorbis", "Opus", "Source"}
    };
    if (arr_acodec[c1][c21] != "") {
        acodec = "Audio: " + arr_acodec[c1][c21] + ", ";
    }
    QString arr_bitrate[5][17] = {
        {"384k",  "320k",  "256k",  "192k",  "128k",  "96k",   "",      "",      "",      "",      "",     "",     "",     "",     "",     "",     ""}, // AAC
        {"640k",  "448k",  "384k",  "256k",  "",      "",      "",      "",      "",      "",      "",     "",     "",     "",     "",     "",     ""}, // AC3
        {"3840k", "3072k", "2048k", "1920k", "1536k", "1472k", "1344k", "1280k", "1152k", "1024k", "960k", "768k", "640k", "576k", "512k", "448k", "384k"}, // DTS
        {"448k",  "384k",  "256k",  "128k",  "96k",   "64k",   "",      "",      "",      "",      "",     "",     "",     "",     "",     "",     ""}, // Vorbis
        {"448k",  "384k",  "256k",  "128k",  "96k",   "64k",   "",      "",      "",      "",      "",     "",     "",     "",     "",     "",     ""} // Opus
    };
    if (arr_acodec[c1][c21] == "AAC") {
        abitrate = arr_bitrate[0][c22] + ", ";
    }
    if (arr_acodec[c1][c21] == "AC3") {
        abitrate = arr_bitrate[1][c22] + ", ";
    }
    if (arr_acodec[c1][c21] == "DTS") {
        abitrate = arr_bitrate[2][c22] + ", ";
    }
    if (arr_acodec[c1][c21] == "Vorbis") {
        abitrate = arr_bitrate[3][c22] + ", ";
    }
    if (arr_acodec[c1][c21] == "Opus") {
        abitrate = arr_bitrate[4][c22] + ", ";
    }
    QString cur_preset_name = codec + res + fps + clrspace + mode + preset + pass + hdr + acodec + abitrate + container;
    ui_preset->lineEdit_presetname->setText(cur_preset_name);
}

void Preset::on_comboBox_container_currentTextChanged()  //******************* Signal Container currentText changed ********//
{
    _repeat++;
}

void Preset::on_comboBox_bitrate_currentTextChanged()  //********************** Signal Bitrate currentText changed *********//
{
    _repeat++;
}

void Preset::on_comboBox_bitrate_editTextChanged()  //*************************** Signal Bitrate editText changed **********//
{
    _repeat++;
}

void Preset::on_comboBox_width_editTextChanged()  //****************************** Signal Width editText changed ***********//
{
    _repeat++;
}

void Preset::on_comboBox_height_editTextChanged()  //***************************** Signal Height editText changed **********//
{
    _repeat++;
}

void Preset::on_comboBox_preset_currentIndexChanged(int index) //******************* Signal Preset index changed ***********//
{
    std::cout << "Index of Preset: " << index << std::endl;
    _repeat++;
}

void Preset::on_comboBox_pass_currentIndexChanged(int index)  //********************* Signal Pass index changed ************//
{
    std::cout << "Index of Pass: " << index << std::endl;
    _repeat++;
}

void Preset::on_comboBox_audio_bitrate_currentTextChanged()  //**************** Signal Abitrate currentText changed ********//
{
    _repeat++;
}

void Preset::repeat_handler()  //********************************************************** Repeat handler *****************//
{
    std::cout << "Call by timer... Repeat count: " << _repeat << std::endl;
    if (_repeat > 0) {
        _repeat = 0;
        change_preset_name();
    }
}

bool Preset::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) // *************** Reset ************************* //
    {
        QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event);
        if (mouse_event->button() == Qt::LeftButton)
        {
            QGuiApplication::restoreOverrideCursor();
            clickPressedFlag = false;
            clickPressed_Left_ResizeFlag = false;
            clickPressed_Left_Top_ResizeFlag = false;
            clickPressed_Top_ResizeFlag = false;
            clickPressed_Right_Top_ResizeFlag = false;
            clickPressed_Right_ResizeFlag = false;
            clickPressed_Right_Bottom_ResizeFlag = false;
            clickPressed_Bottom_ResizeFlag = false;
            clickPressed_Left_Bottom_ResizeFlag = false;
            return QDialog::eventFilter(watched, event);
        }
        return QDialog::eventFilter(watched, event);
    }

    if (watched == ui_preset->widget) // *************** Resize window realisation ************************* //
    {
        if (!this->isMaximized())
        {
            if (event->type() == QEvent::HoverLeave)
            {
                QGuiApplication::setOverrideCursor(Qt::ArrowCursor);
                return QDialog::eventFilter(watched, event);
            }
            if (event->type() == QEvent::HoverMove && !clickPressed_Left_ResizeFlag
                     && !clickPressed_Left_Top_ResizeFlag && !clickPressed_Top_ResizeFlag
                     && !clickPressed_Right_Top_ResizeFlag && !clickPressed_Right_ResizeFlag
                     && !clickPressed_Right_Bottom_ResizeFlag && !clickPressed_Bottom_ResizeFlag
                     && !clickPressed_Left_Bottom_ResizeFlag)
            {
                curWidth = this->width();
                curHeight = this->height();
                mouseCoordinate = ui_preset->widget->mapFromGlobal(QCursor::pos());
                if ((mouseCoordinate.x() < 6) && (mouseCoordinate.y() > 62) && (mouseCoordinate.y() < (curHeight - 6)))
                {
                    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
                    return QDialog::eventFilter(watched, event);
                }
                if ((mouseCoordinate.x() < 6) && (mouseCoordinate.y() < 6))
                {
                    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
                    return QDialog::eventFilter(watched, event);
                }
                if ((mouseCoordinate.x() > 6) && (mouseCoordinate.x() < (curWidth - 120)) && (mouseCoordinate.y() < 3))
                {
                    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
                    return QDialog::eventFilter(watched, event);
                }
                if ((mouseCoordinate.x() > (curWidth - 6)) && (mouseCoordinate.y() < 6))
                {
                    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeBDiagCursor));
                    return QDialog::eventFilter(watched, event);
                }
                if ((mouseCoordinate.x() > (curWidth - 6)) && (mouseCoordinate.y() > 62) && (mouseCoordinate.y() < (curHeight - 6)))
                {
                    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
                    return QDialog::eventFilter(watched, event);
                }
                if ((mouseCoordinate.x() > (curWidth - 6)) && (mouseCoordinate.y() > (curHeight - 6)))
                {
                    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
                    return QDialog::eventFilter(watched, event);
                }
                if ((mouseCoordinate.x() > 6) && (mouseCoordinate.x() < (curWidth - 6)) && (mouseCoordinate.y() > (curHeight - 6)))
                {
                    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
                    return QDialog::eventFilter(watched, event);
                }
                if ((mouseCoordinate.x() < 6) && (mouseCoordinate.y() > (curHeight - 6)))
                {
                    QGuiApplication::setOverrideCursor(QCursor(Qt::SizeBDiagCursor));
                    return QDialog::eventFilter(watched, event);
                }
                QGuiApplication::setOverrideCursor(Qt::ArrowCursor);
                return QDialog::eventFilter(watched, event);
            }
            if (event->type() == QEvent::MouseButtonPress)
            {
                QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event);
                if (mouse_event->button() == Qt::LeftButton)
                {
                    oldWidth = this->width();
                    oldHeight = this->height();
                    mouseClickCoordinate = mouse_event->pos();
                    if ((mouseClickCoordinate.x() < 6) && (mouseClickCoordinate.y() > 62) && (mouseClickCoordinate.y() < (oldHeight - 6)))
                    {
                        clickPressed_Left_ResizeFlag = true;
                        return QDialog::eventFilter(watched, event);
                    }
                    if ((mouseClickCoordinate.x() < 6) && (mouseClickCoordinate.y() < 6))
                    {
                        clickPressed_Left_Top_ResizeFlag = true;
                        return QDialog::eventFilter(watched, event);
                    }
                    if ((mouseClickCoordinate.x() > 6) && (mouseClickCoordinate.x() < (oldWidth - 120)) && (mouseClickCoordinate.y() < 3))
                    {
                        clickPressed_Top_ResizeFlag = true;
                        return QDialog::eventFilter(watched, event);
                    }
                    if ((mouseClickCoordinate.x() > (oldWidth - 6)) && (mouseClickCoordinate.y() < 6))
                    {
                        clickPressed_Right_Top_ResizeFlag = true;
                        return QDialog::eventFilter(watched, event);
                    }
                    if ((mouseClickCoordinate.x() > (oldWidth - 6)) && (mouseClickCoordinate.y() > 62) && (mouseClickCoordinate.y() < (oldHeight - 6)))
                    {
                        clickPressed_Right_ResizeFlag = true;
                        return QDialog::eventFilter(watched, event);
                    }
                    if ((mouseClickCoordinate.x() > (oldWidth - 6)) && (mouseClickCoordinate.y() > (oldHeight - 6)))
                    {
                        clickPressed_Right_Bottom_ResizeFlag = true;
                        return QDialog::eventFilter(watched, event);
                    }
                    if ((mouseClickCoordinate.x() > 6) && (mouseClickCoordinate.x() < (oldWidth - 6)) && (mouseClickCoordinate.y() > (oldHeight - 6)))
                    {
                        clickPressed_Bottom_ResizeFlag = true;
                        return QDialog::eventFilter(watched, event);
                    }
                    if ((mouseClickCoordinate.x() < 6) && (mouseClickCoordinate.y() > (oldHeight - 6)))
                    {
                        clickPressed_Left_Bottom_ResizeFlag = true;
                        return QDialog::eventFilter(watched, event);
                    }
                    return QDialog::eventFilter(watched, event);
                }
                return QDialog::eventFilter(watched, event);
            }
            if (event->type() == QEvent::MouseMove)
            {
                QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event);
                if (mouse_event->buttons() & Qt::LeftButton)
                {
                    int deltaX = mouse_event->globalPos().x() - mouseClickCoordinate.x();
                    int deltaY = mouse_event->globalPos().y() - mouseClickCoordinate.y();
                    int deltaWidth = static_cast<int>(mouse_event->localPos().x()) - mouseClickCoordinate.x();
                    int deltaHeight = static_cast<int>(mouse_event->localPos().y()) - mouseClickCoordinate.y();
                    if (clickPressed_Left_ResizeFlag)
                    {
                        this->setGeometry(deltaX, this->pos().y(), this->width() - deltaWidth, oldHeight);
                        return QDialog::eventFilter(watched, event);
                    }
                    if (clickPressed_Left_Top_ResizeFlag)
                    {
                        this->setGeometry(deltaX, deltaY, this->width() - deltaWidth, this->height() - deltaHeight);
                        return QDialog::eventFilter(watched, event);
                    }
                    if (clickPressed_Top_ResizeFlag)
                    {
                        this->setGeometry(this->pos().x(), deltaY, oldWidth, this->height() - deltaHeight);
                        return QDialog::eventFilter(watched, event);
                    }
                    if (clickPressed_Right_Top_ResizeFlag)
                    {
                        this->setGeometry(this->pos().x(), deltaY, oldWidth + deltaWidth, this->height() - deltaHeight);
                        return QDialog::eventFilter(watched, event);
                    }
                    if (clickPressed_Right_ResizeFlag)
                    {
                        this->setGeometry(this->pos().x(), this->pos().y(), oldWidth + deltaWidth, oldHeight);
                        return QDialog::eventFilter(watched, event);
                    }
                    if (clickPressed_Right_Bottom_ResizeFlag)
                    {
                        this->setGeometry(this->pos().x(), this->pos().y(), oldWidth + deltaWidth, oldHeight + deltaHeight);
                        return QDialog::eventFilter(watched, event);
                    }
                    if (clickPressed_Bottom_ResizeFlag)
                    {
                        this->setGeometry(this->pos().x(), this->pos().y(), oldWidth, oldHeight + deltaHeight);
                        return QDialog::eventFilter(watched, event);
                    }
                    if (clickPressed_Left_Bottom_ResizeFlag)
                    {
                        this->setGeometry(deltaX, this->pos().y(), this->width() - deltaWidth, oldHeight + deltaHeight);
                        return QDialog::eventFilter(watched, event);
                    }
                    return QDialog::eventFilter(watched, event);
                }
                return QDialog::eventFilter(watched, event);
            }
            return QDialog::eventFilter(watched, event);
        }
        return QDialog::eventFilter(watched, event);
    }

    if (watched == ui_preset->frame_hint) // *************** Drag window realisation ************************* //
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event);
            if (mouse_event->button() == Qt::LeftButton)
            {
                mouseClickCoordinate = mouse_event->pos();
                clickPressedFlag = true;
                return QDialog::eventFilter(watched, event);
            }
            return QDialog::eventFilter(watched, event);
        }
        if ((event->type() == QEvent::MouseMove) && clickPressedFlag == true)
        {
            QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event);
            if (mouse_event->buttons() & Qt::LeftButton)
            {
                if (this->isMaximized())
                {
                    on_expandWindow_2_clicked();
                }
                this->move(mouse_event->globalPos() - mouseClickCoordinate);
                return QDialog::eventFilter(watched, event);
            }
            return QDialog::eventFilter(watched, event);
        }
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            QMouseEvent* mouse_event = dynamic_cast<QMouseEvent*>(event);
            if (mouse_event->buttons() & Qt::LeftButton)
            {
                on_expandWindow_2_clicked();
                return QDialog::eventFilter(watched, event);
            }
            return QDialog::eventFilter(watched, event);
        }
        return QDialog::eventFilter(watched, event);
    }
    return QDialog::eventFilter(watched, event);
}

