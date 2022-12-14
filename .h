#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>
#include <dt-bindings/zmk/bt.h>
#include <dt-bindings/zmk/mouse.h>

#include "../zmk-nodefree-config/keypos_def/keypos_42keys.h"
#include "../zmk-nodefree-config/helper.h"

#define Base 0
#define Num 1
#define Nav 2
#define Media 3
#define Vim 4

#include "combos.dtsi"  // must be sourced after layer-shortcuts
#include "mouse.dtsi"

#define QUICK_TAP_MS 175

&sk {  // sticky-key config
    release-after-ms = <600>;  // release after 0.6s
    quick-release;             // no double capitalization when rolling keys
};

&sl {  // sticky-layer config
    ignore-modifiers;
};

&mt {
    flavor = "tap-preferred";
    tapping-term-ms = <220>;
    quick-tap-ms = <220>;              // repeat on tap-into-hold
    hold-trigger-key-positions = <0>;  // tap on interrupt
};

#define NAV_LEFT  &mt HOME     LEFT    // tap: left  | long-tap: beginning of line
#define NAV_RIGHT &mt END      RIGHT   // tap: right | long-tap: end       of line
#define NAV_UP    &mt LC(HOME) UP      // tap: up    | long-tap: beginning of document
#define NAV_DOWN  &mt LC(END)  DOWN    // tap: down  | long-tap: end       of document
#define NAV_BSPC  &mt LC(BSPC) BSPC    // tap: bspc  | long-tap: delete word backward
#define NAV_DEL   &mt LC(DEL)  DEL     // tap: del   | long-tap: delete word forward

&lt {
    quick_tap_ms = <150>;
};

&caps_word {  // mods deactivate caps-word, requires PR #1441
    /delete-property/ ignore-modifiers;
};

/* Homerow mods */

#define KEYS_L LT0 LT1 LT2 LT3 LT4 LM0 LM1 LM2 LM3 LM4 LB0 LB1 LB2 LB3 LB4  // left-hand keys
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RM0 RM1 RM2 RM3 RM4 RB0 RB1 RB2 RB3 RB4  // right-hand keys
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                                      // thumb keys

ZMK_BEHAVIOR(hml, hold_tap,  // left-hand HRMs
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <QUICK_TAP_MS>;
    global-quick-tap-ms = <150>;        // requires PR #1387
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_R THUMBS>;
    hold-trigger-on-release;            // requires PR #1423
)

ZMK_BEHAVIOR(hmr, hold_tap,  // right-hand HRMs
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <QUICK_TAP_MS>;
    global-quick-tap-ms = <150>;        // requires PR #1387
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_L THUMBS>;
    hold-trigger-on-release;            // requires PR #1423
)

ZMK_BEHAVIOR(fn_td, hold_tap,  // right-hand HRMs
    flavor = "tap-preferred";
    tapping-term-ms = <300>;
    quick-tap-ms = <0>;
    bindings = <&kp>, <&kp>;
)

// tap: backspace | lshft + tap: delete | rshft + tap: shift-delete | hold: num layer
ZMK_BEHAVIOR(bs_del_media, mod_morph,
    bindings = <&lt Media BSPC>, <&kp DEL>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
    keep-mods = <MOD_LSFT>;  // requires PR #1412
)

// tap: copy | double-tap: cut
ZMK_BEHAVIOR(copy_cut, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&kp LC(INS)>, <&kp LC(X)>;
)

// tap: space | space + tap: dot -> space -> sticky shift | hold: activate layer
ZMK_BEHAVIOR(dot_spc, macro,
    wait-ms = <0>;
    tap-ms = <5>;
    bindings = <&kp DOT &kp SPACE &sk LSHFT>;
)
ZMK_BEHAVIOR(spc_morph, mod_morph,
    bindings = <&kp SPACE>, <&dot_spc>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)
ZMK_BEHAVIOR(lt_spc, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <200>;
    quick-tap-ms = <QUICK_TAP_MS>;
    bindings = <&mo>, <&spc_morph>;
)

// vim: change inner word
ZMK_BEHAVIOR(ciw, macro,
    wait-ms = <0>;
    tap-ms = <5>;
    bindings = <&kp C &kp I &kp W>;
)
ZMK_BEHAVIOR(ciwc, macro,
    wait-ms = <0>;
    tap-ms = <5>;
    bindings = <&kp C &kp I &kp LS(W)>;
)
ZMK_BEHAVIOR(vim_ciw, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&ciw>, <&ciwc>;
)

// vim: delete inner word
ZMK_BEHAVIOR(diw, macro,
    wait-ms = <0>;
    tap-ms = <5>;
    bindings = <&kp D &kp I &kp W>;
)
ZMK_BEHAVIOR(diwc, macro,
    wait-ms = <0>;
    tap-ms = <5>;
    bindings = <&kp D &kp I &kp LS(W)>;
)
ZMK_BEHAVIOR(vim_diw, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&diw>, <&diwc>;
)

ZMK_BEHAVIOR(vim_q, macro,
    wait-ms = <0>;
    tap-ms = <5>;
    bindings = <&kp COLON &kp Q &kp EXCL &kp RET>;
)

ZMK_BEHAVIOR(colon_quote, tap_dance,
    tapping-term-ms = <300>;
    bindings = <&kp APOS>, <&kp COLON>;
)

ZMK_BEHAVIOR(par_td, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&kp LPAR>, <&kp RPAR>;
)
ZMK_BEHAVIOR(bkt_td, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&kp LBKT>, <&kp RBKT>;
)
ZMK_BEHAVIOR(brc_td, tap_dance,
    tapping-term-ms = <300>;
    bindings = <&kp LBRC>, <&kp RBRC>;
)
ZMK_BEHAVIOR(lt_gt, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&kp LT>, <&kp GT>;
)
ZMK_BEHAVIOR(at_amps, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&kp AT>, <&kp AMPS>;
)

/ {
    keymap {
        compatible = "zmk,keymap";

        default_layer {
          label = "Base";
            bindings = <
            &kp TAB    &kp Q         &kp W         &kp F           &kp P             &kp B                 &kp J      &kp L           &kp U         &kp Y        &colon_quote   &to Nav
            &kp ESC    &hml LGUI A   &hml LALT R   &hml LCTRL S    &hml LSHIFT T     &kp G                 &kp M      &hmr RSHIFT N   &hmr LCTRL E  &hmr LALT I  &hmr RGUI O    &key_repeat
            &mo Vim    &kp Z         &kp X         &kp C           &kp D             &kp V                 &kp K      &kp H           &kp COMMA     &kp DOT      &kp FSLH       &to Media
                                                   &mo Nav         &lt_spc Media 0   &sk LSHIFT            &mo Num    &bs_del_media   &kp LCTRL
        >;
        };
        num_layer {
            label = "Num";
            bindings = <
            &trans   &kp TILDE     &fn_td F7 N7   &fn_td F8 N8   &fn_td F9 N9   &kp EQUAL             &at_amps    &par_td    &bkt_td    &brc_td       &trans           &trans
            &trans   &kp STAR      &fn_td F4 N4   &fn_td F5 N5   &fn_td F6 N6   &kp MINUS             &kp H       &kp J      &kp K      &hmr RALT L   &hmr LGUI SEMI    &trans
            &trans   &kp PIPE      &fn_td F1 N1   &fn_td F2 N2   &fn_td F3 N3   &kp CARET             &kp DLLR    &kp HASH   &trans     &trans        &trans           &trans
                                                  &fn_td F10 N0    &trans         &trans                &none       &trans     &trans
        >;
        };
        nav_layer {
            label = "Nav";
            bindings = <
            &trans       &kp TAB   &kp LS(TAB) &copy_cut        &kp LS(INS)   &kp K_UNDO           &none      NAV_BSPC    NAV_DEL      &none      &none   &none 
            &trans       &sk LGUI  &sk LALT    &sk LCTRL        &sk LSHIFT    &kp LG(F)            NAV_LEFT   NAV_DOWN    NAV_UP       NAV_RIGHT  &none   &none
            &trans       &kp F5    &kp LC(W)   &kp LC(LS(TAB))  &kp RC(TAB)   &kp LC(LS(T))        &kp HOME   &kp PG_DN   &kp PG_UP    &kp END    &kp INS &trans
                                               &trans           &kp PRSC      &trans               &trans     &trans      &trans
        >;
        };
        media_layer {
            label = "Media";
            bindings = <
            &trans   &kp PG_UP   &none       NAV_UP      &kp K_VOL_DN    &kp K_VOL_UP         &mwh SCROLL_UP      &mkp LCLK       &mmv MOVE_UP    &mkp RCLK         &mwh SCROLL_LEFT    &trans
            &trans   &kp PG_DN   NAV_LEFT    NAV_DOWN    NAV_RIGHT       &none                &mwh SCROLL_DOWN    &mmv MOVE_LEFT  &mmv MOVE_DOWN  &mmv MOVE_RIGHT   &mwh SCROLL_RIGHT   &trans
            &trans   &kp LG(N1)   &kp LG(N2)   &kp LG(N3)   &kp LG(N4)       &kp LG(N5)            &bt BT_CLR          &bt BT_SEL 0    &bt BT_SEL 1    &bt BT_SEL 2      &bt BT_SEL 3        &trans
                                             &trans      &trans          &trans               &trans              &trans          &trans
        >;
        };
        vim_layer {
            label = "Vim";
            bindings = <
            &trans   &vim_q       &none       &none       &none       &none           &kp LC(U)     &none  &none   &none   &none   &none   
            &trans   &none        &none       &none       &none       &none           &kp LC(D)     &none  &none   &none   &none   &none      
            &trans   &kp LG(Z)    &kp LG(X)   &vim_ciw    &vim_diw    &none           &none         &none   &none  &none   &none   &none   
                                               &trans     &trans      &trans          &trans        &kp LC(W)         &trans
        >;
        };
    };
};
