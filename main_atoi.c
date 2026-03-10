#include <stdio.h>
#include <uchar.h>

extern long ft_atoi_base_utf32(const char32_t *str, const char32_t *base);

static char32_t *base = U"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*.,/:;<=>?@[]^_`{|}~"
    U"¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
    U"ĀāĂăĄąĆćĈĉĊċČčĎďĐđĒēĔĕĖėĘęĚěĜĝĞğĠġĢģĤĥĦħĨĩĪīĬĭĮįİıĲĳĴĵĶķĸĹĺĻļĽľĿŀŁłŃńŅņŇňŉŊŋŌōŎŏŐőŒœŔŕŖŗŘřŚśŜŝŞşŠšŢţŤťŦŧŨũŪūŬŭŮůŰűŲųŴŵŶŷŸŹźŻżŽž"
    U"ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩαβγδεζηθικλμνξοπρστυφχψω"
    U"БГДЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя"
    U"←↑→↓↔↕↖↗↘↙↚↛↜↝↞↟↠↡↢↣↤↥↦↧↨↩↪↫↬↭↮↯↰↱↲↳↴↵↶↷↸↹↺↻↼↽↾↿⇀⇁⇂⇃⇄⇅⇆⇇⇈⇉⇊⇋⇌⇍⇎⇏⇐⇑⇒⇓⇔⇕⇖⇗⇘⇙⇚⇛⇜⇝⇞⇟⇠";

static int pass = 0;
static int fail = 0;

static void check(const char *label, long got, long expected)
{
    if (got == expected)
    {
        printf("  [OK] %s → %ld\n", label, got);
        pass++;
    }
    else
    {
        printf("  [KO] %s → got %ld, expected %ld\n", label, got, expected);
        fail++;
    }
}

// U = UTF32

int main()
{
    printf("=== Cas normaux ===\n");
    check("\"0\" base10",        ft_atoi_base_utf32(U"0",    U"0123456789"), 0);
    check("\"42\" base10",       ft_atoi_base_utf32(U"42",   U"0123456789"), 42);
    check("\"-42\" base10",      ft_atoi_base_utf32(U"-42",  U"0123456789"), -42);
    check("\"+42\" base10",      ft_atoi_base_utf32(U"+42",  U"0123456789"), 42);
    check("\"1234\" base10",     ft_atoi_base_utf32(U"1234", U"0123456789"), 1234);

    printf("\n=== Whitespace ===\n");
    check("\"  42\" spaces",     ft_atoi_base_utf32(U"  42",    U"0123456789"), 42);
    check("\"\\t\\n42\"",        ft_atoi_base_utf32(U"\t\n42",  U"0123456789"), 42);
    check("\"  -42\" spaces",    ft_atoi_base_utf32(U"  -42",   U"0123456789"), -42);

    printf("\n=== Multiple signes ===\n");
    check("\"---+--+1234\"",     ft_atoi_base_utf32(U"---+--+1234", U"0123456789"), -1234);
    check("\"--42\"",            ft_atoi_base_utf32(U"--42",        U"0123456789"), 42);
    check("\"---42\"",           ft_atoi_base_utf32(U"---42",       U"0123456789"), -42);
    check("\"++++42\"",          ft_atoi_base_utf32(U"++++42",      U"0123456789"), 42);

    printf("\n=== Stop au premier char invalide ===\n");
    check("\"1234ab\"",          ft_atoi_base_utf32(U"1234ab",  U"0123456789"), 1234);
    check("\"12 34\"",           ft_atoi_base_utf32(U"12 34",   U"0123456789"), 12);
    check("\"abc\" base16",      ft_atoi_base_utf32(U"abc",     U"0123456789abcdef"), 2748);

    printf("\n=== Bases invalides → 0 ===\n");
    check("base vide",           ft_atoi_base_utf32(U"42",  U""), 0);
    check("base 1 char",         ft_atoi_base_utf32(U"42",  U"0"), 0);
    check("base avec '+'",       ft_atoi_base_utf32(U"42",  U"0123456789+"), 0);
    check("base avec '-'",       ft_atoi_base_utf32(U"42",  U"0123456789-"), 0);
    check("base avec espace",    ft_atoi_base_utf32(U"42",  U"01 3456789"), 0);
    check("base avec doublon",   ft_atoi_base_utf32(U"42",  U"0123456789a5"), 0);

    printf("\n=== Base binaire ===\n");
    check("\"101\" base2",       ft_atoi_base_utf32(U"101",  U"01"), 5);
    check("\"-1010\" base2",     ft_atoi_base_utf32(U"-1010",U"01"), -10);

    printf("\n=== Base hex ===\n");
    check("\"ff\" base16",       ft_atoi_base_utf32(U"ff",   U"0123456789abcdef"), 255);
    check("\"deadbeef\"",        ft_atoi_base_utf32(U"deadbeef", U"0123456789abcdef"), 3735928559L);

    printf("\n=== Base 36 ===\n");
    check("\"za123\" base36",    ft_atoi_base_utf32(U"za123",
        U"0123456789abcdefghijklmnopqrstuvwxyz"), 59254491);
    
    printf("\n=== Base UTF-32 géante (base 500) ===\n");
    check("\"⇌\" index 479",     ft_atoi_base_utf32(U"⇌",   base), 479);
    check("\"⇟\" index 498",     ft_atoi_base_utf32(U"⇟",   base), 498);
    check("\"⇠\" index 499", ft_atoi_base_utf32(U"⇠", base), 499);
    check("\"0\" dans base 500",  ft_atoi_base_utf32(U"0",   base), 0);
   

    printf("\n=== Résultat : %d OK, %d KO ===\n", pass, fail);

    return 0;
}

// https://baseconvert.com/?hexadecimal=deadbeef&decimal&binary&octal&roman-numerals&balanced-ternary


// nasm -f elf64 ft_base_strlen_check.s                                                                                                                                                                            1 ✘ 
// nasm -f elf64 ft_is_base_dups.s
// nasm -f elf64 ft_find_char_index.s 
// nasm -f elf64 ft_atoi_base_utf32.s
// nasm -f elf64  ft_check_string 
// cc *.o main.c