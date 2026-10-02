//================
//ASCII ART SYSTEM
//================
//Provides visual ASCII art for the headers, banners and decorations
//To make the CLI quiz look amazing with a professional polish

//Designer Philosophy
//-Each major screen gets unique ASCII art
//-Game modes have distinctive visual identities
//-Results screens are celebratory and encouraging
//-All art uses standard ASCII characters 

#ifndef ASCIIART_H
#define ASCIIART_H

namespace AsciiArt{
    //MAIN BRANDING
    //Display the main codemaster logo
    void display_main_logo();

    //GAME MODE BANNERS
    void display_classic_banner();
    void display_quick_attack_banner();
    void display_survival_banner();
    void display_marathon_banner();
    void display_lightning_banner();
    void display_practice_banner();

    //RESULT SCREENS
    void display_perfect_victory();
    void display_great_victory();
    void display_good_victory();
    void display_game_over();

    //DECORATIVE ELEMENTS
    void display_trophy();
    void display_seperator_thick();
    void display_separator_double();
}


#endif