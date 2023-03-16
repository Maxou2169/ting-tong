#include "includes/balle.h"
#include "includes/vec2.h"
#include "includes/joueur.h"
#include "includes/terrain.h"
#include "includes/affichage.h"
#include "includes/score.h"
#include "includes/coup.h"
#include "includes/format.h"
#include "includes/texte.h"

bool run_test(void);

int main(void)
{
    run_test();
    Terrain t(Joueur("J1", Vec2(60.0,150.0)), Joueur("J2", Vec2(60.0,60.0)), Balle(Vec2(60.0, 60.0), Vec2(10.0, 10.0)));
    //t.get_balle().set_traj(Vec2(0, 2));
    Texte tx(t);
    tx.texte();
    Affichage a(t);
    a.render_loop();
    return (0);
}

bool run_test(void)
{
    Vec2 v(0, 0);
    v.test();

    Balle b(Vec2(0, 0), Vec2(0, 0));
    b.test();

    Joueur j("J1", Vec2(0, 0));
    j.test();

    Terrain t(Joueur("J1", Vec2(0, 0)), Joueur("J2", Vec2(0, 0)), Balle(Vec2(0, 0), Vec2(0, 0)));
    t.test();

    Affichage a(t,1,1);
    a.test();

    Score sc = Score();
    sc.test();

    Coup c = Coup(j, b);
    c.test();

    Format f = Format();
    f.test();
    return (true);
}