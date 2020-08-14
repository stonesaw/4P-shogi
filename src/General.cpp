#include "General.h"


/* class Window */
void Window::DrawBG(int red, int green, int blue) {
    DrawBox(0, 0, this->width, this->height, GetColor(red, green, blue), TRUE);
}


/* class Mouse */
void Mouse::Update() {
    GetMousePoint(&posX, &posY);
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
        this->is_click = true;
    else
        this->is_click = false;
}


bool Mouse::isBanOn(Ban ban) {
    if (ban.ox <= this->posX && this->posX < ban.ox + ban.size - ban.line_width &&
        ban.oy <= this->posY && this->posY < ban.oy + ban.size - ban.line_width) {
        return true;
    }
    else {
        return false;
    }
}

bool Mouse::isClick() {
    return this->is_click;
}


void Mouse::SetMapPoint(Ban ban) {
    if (this->isBanOn(ban)) {
        this->mapX = (this->posX - ban.ox) / ban.masu_size;
        this->mapY = (this->posY - ban.oy) / ban.masu_size;
    }
    else {
        this->mapX = -1;
        this->mapY = -1;
    }
}


void Mouse::DrawBanShade(Ban ban) {
    if (isClick()) {
        /*if (isBanOn(ban) && chooseX == mapX && chooseY == mapY) {
            this->isChoose = !this->isChoose;
        }*/
        if (isBanOn(ban)) {
             this->isChoose = true;
             this->chooseX = mapX;
             this->chooseY = mapY;
        }
        else
            this->isChoose = false;
    }
    if (this->isChoose) {
        DrawBox(ban.ox + this->chooseX   * ban.masu_size, ban.oy + this->chooseY * ban.masu_size,
            ban.ox + (this->chooseX + 1) * ban.masu_size, ban.oy + (this->chooseY + 1) * ban.masu_size,
            GetColor(255, 0, 0), TRUE);
    }
    if (this->isBanOn(ban) && !(chooseX == mapX && chooseY == mapY)) {
        DrawBox(ban.ox + this->mapX * ban.masu_size, ban.oy + this->mapY * ban.masu_size,
            ban.ox + (this->mapX + 1) * ban.masu_size, ban.oy + (this->mapY + 1) * ban.masu_size,
            GetColor(240, 181, 46), TRUE);
    }
}


/* class Ban */
Ban::Ban(Window window, int color, double base_scale, double scale, int line_width) {
    int windowMinSize = min(window.width, window.height);
    this->base_scale = base_scale;
    this->base_width = windowMinSize * base_scale;
    this->base_height = windowMinSize * base_scale;
    this->base_ox = (window.width - this->base_width) / 2;
    this->base_oy = (window.height - this->base_height) / 2;

    this->scale = scale;
    this->size = (int)(this->base_width * this->scale);
    this->ox = this->base_ox + (this->base_width - this->size) / 2;
    this->oy = this->base_oy + (this->base_height - this->size) / 2;
    this->masu_size = (this->size / 9);
    this->color = color;
    this->line_width = line_width * window.scale;
}


void Ban::DrawBase() {
    DrawBox(this->base_ox, this->base_oy, this->base_ox + this->base_width, this->base_oy + this->base_height, this->color, TRUE);
}


void Ban::DrawFrame() {
    for (int y = 0; y < 10; y++) {
        DrawBox(this->ox,              this->oy + y * this->masu_size,
                this->ox + this->size, this->oy + y * this->masu_size + this->line_width,
                GetColor(0, 0, 0), TRUE);
    }
    for (int x = 0; x < 10; x++) {
        DrawBox(this->ox + x * this->masu_size,                    this->oy,
                this->ox + x * this->masu_size + this->line_width, this->oy + this->size,
                GetColor(0, 0, 0), TRUE);
    }
}


void Ban::DrawPiece(Calc calc, std::map<std::string, int> image) { 
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            // TO DO : DrawFormatString() -> DrawExtendGraph()
            // masu_size‚ð‡‚í‚¹‚Ä•`‰æ(Šg‘åork¬)
            // Calc::id2name‚ðŽg‚Á‚Äid‚ðname‚É’u‚«Š·‚¦‚Ä...
            // image["‹î‚Ì–¼‘O"] ‚Åhandle‚ªŽæ‚ê‚é

            DrawFormatString(this->ox + this->masu_size * x, this->oy + this->masu_size * y,
                GetColor(0, 0, 0), "%d:%d", calc.board[y + 1][x + 1].player, calc.board[y + 1][x + 1].id);
            // •ÏX’†chisato
            /* DrawExtendGraph(this->ox + this->masu_size * x, this->oy + this->masu_size * y,
               this->ox + this->masu_size * (x + 1), this->oy + this->masu_size * (y + 1), );*/
        
        }
    }
}


/* class ImageLoader */
bool ImageLoader::file_exists(const char* str) {
    std::ifstream fs(str);
    return fs.is_open();
}


std::map<std::string, int> ImageLoader::Load(std::vector<std::vector<std::string>> nameAndPath) {
    std::map<std::string, int> map;
    for (size_t i = 0; i < nameAndPath.size(); i++) {
        std::string name = nameAndPath.at(i).at(0);
        std::string path = nameAndPath.at(i).at(1);

        int graph = LoadGraph(path.c_str());
        if (graph != -1)
            map[name] = graph;
        else
            throw std::invalid_argument("ImageLoder::Load() [File Load Error '" + path + "']");
    }

    return map;
}


std::vector<std::vector<std::string>> ImageLoader::data = {
    { "fu",      "./lib/image/fuhyou.png" },
    { "kyo",     "./lib/image/kyousha.png" },
    { "kei",     "./lib/image/keima.png" },
    { "gin",     "./lib/image/ginshou.png" },
    { "kin",     "./lib/image/kinshou.png" },
    { "kaku",    "./lib/image/kakugyou.png" },
    { "hisya",   "./lib/image/hisha.png" },
    { "ou",      "./lib/image/oushou.png" },
    { "tokin",   "./lib/image/tokin.png" },
    { "narikyo", "./lib/image/narikyou.png" },
    { "narikei", "./lib/image/narikei.png" },
    { "narigin", "./lib/image/narigin.png" },
    { "uma",     "./lib/image/ryuuma.png" },
    { "ryu",     "./lib/image/ryuuou.png" }
};


void ImageLoader::currentDir() {
    std::filesystem::path path = std::filesystem::current_path();
    std::cout << "Current Directory: " << path.string() << std::endl;
}

