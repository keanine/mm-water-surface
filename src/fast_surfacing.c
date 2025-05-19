#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

extern void func_80848250(PlayState* play, Player* this);
extern void func_808353DC(PlayState* play, Player* this);
extern void func_8082DC64(PlayState* play, Player* this);
extern void Player_AnimSfx_PlayVoice(Player* this, u16 sfxId);

PlayState* gPlay;
Player* gThis;

// RECOMP_PATCH void Player_Action_60(Player* this, PlayState* play) {
//     if ((this->actor.depthInWater - this->actor.velocity.y) < this->ageProperties->unk_30 + 5) {
//         func_80848250(play, this);
//         func_808353DC(play, this);
//         func_8082DC64(play, this);
//         Player_AnimSfx_PlayVoice(this, NA_SE_VO_LI_BREATH_DRINK);
//     }
// }

RECOMP_HOOK("Player_Action_60") void Player_Action_60(Player* this, PlayState* play) {
    gThis = this;
    gPlay = play;
}

RECOMP_HOOK_RETURN("Player_Action_60") void Player_Action_60_Return() {
    f32 relX = -(gPlay->state.input[0].rel.stick_x / 60.0);
    f32 relY = (gPlay->state.input[0].rel.stick_y / 60.0);

    if (relX != 0 || relY != 0) {
        if ((gThis->actor.depthInWater - gThis->actor.velocity.y) < gThis->ageProperties->unk_30 + 5) {
            if (gThis->skelAnime.curFrame < 5.0f) {
                Player_AnimSfx_PlayVoice(gThis, NA_SE_VO_LI_BREATH_DRINK);
            }
            func_80848250(gPlay, gThis);
            func_808353DC(gPlay, gThis);
            func_8082DC64(gPlay, gThis);
        }
    }
}