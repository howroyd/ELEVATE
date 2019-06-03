#include "__cf_battery_eq_circuit_pascal5_single_shot_stack.h"
#ifndef RTW_HEADER_battery_eq_circuit_pascal5_single_shot_stack_h_
#define RTW_HEADER_battery_eq_circuit_pascal5_single_shot_stack_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef battery_eq_circuit_pascal5_single_shot_stack_COMMON_INCLUDES_
#define battery_eq_circuit_pascal5_single_shot_stack_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "sigstream_rtw.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "battery_eq_circuit_pascal5_single_shot_stack_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#define MODEL_NAME battery_eq_circuit_pascal5_single_shot_stack
#define NSAMPLE_TIMES (2) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (506) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T adontzi2bo [ 4 ] ; real_T nz5y5utmro [ 4 ] ; real_T
jum15pqqg1 ; real_T az0hrbqkrf ; real_T daplgb1rla ; real_T jdfrz34ab5 ;
real_T lujepfroun ; real_T gywgkp2di0 ; real_T n1mhwe4wmc [ 200 ] ; real_T
ozjanvc1ks [ 6 ] ; real_T haz3shqct1 [ 4 ] ; real_T mcaon1wt2t ; real_T
f3ooyiusal ; real_T c4oldjnq3u [ 7 ] ; real_T ibvmt2yzmz [ 4 ] ; real_T
c5qmbivysx ; real_T pho3qpftnj ; real_T gcul10z3jv [ 7 ] ; real_T j25efy55r5
[ 4 ] ; real_T ckf4buvedv ; real_T j1sayi1hcj ; real_T mkwy2gpqoc ; real_T
ms1xzaxnje ; real_T cyub2cqqry ; real_T ips0s3kqvl ; real_T prsr21hpu4 ;
real_T ggr0l4ju4n ; real_T dvtnssswgf ; real_T lylp4o3za1 ; real_T a1obnn0rik
; real_T gyntgt3u14 ; real_T fuc132pis2 ; real_T avikq2ugv0 ; real_T
cjwcu33zih ; real_T c1giyep455 ; real_T ibm00zzuip ; real_T c4msc3eeit ;
real_T obirrlzjde ; real_T fv4mwhqp3p ; real_T fylelfokss ; real_T eddfok0ttt
; real_T i2w34spfgq ; real_T mgwpo2euua ; real_T ohgmxf2ovd ; real_T
c2ydbw2sj0 ; real_T mmk3xoxflr ; real_T dawwmoz5xy ; real_T gri0rwhmpf ;
real_T n1zbzuxb3r ; real_T oypzfi1iso ; real_T kkmyyic4sz ; real_T fngwa3baxj
; real_T l5qc2ih1nh ; real_T m21rtdprr4 ; real_T ny2kjgfpce ; real_T
mbcc0zmkwz ; real_T e1vdt0sgzs ; real_T a5ef0qh5ui ; real_T emi1eiicwz ;
real_T ly2a15pyev ; real_T afaqeoaxi3 ; real_T o2vyntsikv ; real_T gh1ihs33dh
; real_T bta1zfrbsx ; real_T j0nzc2e04b ; real_T ilizmh402p ; real_T
mzbg4yn5c1 ; real_T iqbg0iu0hq ; real_T mowq1vn4dj ; real_T crefty5nn2 [ 48 ]
; real_T gaaje2saux ; real_T nxggzjbabc ; real_T jqcc0mn3f3 ; real_T
jjiiu42bv0 ; real_T lbio5fb4ou ; real_T jqxry0xazb ; real_T ckk3filxf3 ;
real_T eallzlne40 ; real_T l0arfstdit ; real_T olpn1if10e ; real_T itefnd2w4j
; real_T asntuwdff0 ; real_T c4skqe1xnw ; real_T l1nvprssra ; real_T
np5zsj2uej ; real_T maz3ovczmz ; real_T oquuznjggf ; real_T mpv2aflj0t ;
real_T nxrrqatnc0 ; real_T hbalbktp1c ; real_T hoo435luju ; real_T jkwsvbgagi
; real_T keanmwalcs ; real_T b2kdpcmjqu ; real_T mwse5jjkay ; real_T
dvf4w152ur ; real_T dwfncuecvl ; real_T je5gfl4unq ; real_T ha2duc3bo5 ;
real_T ijsq3yotwy ; real_T ggil01xfur ; real_T erhhpn02rp ; real_T g3yvot4ehk
; real_T pets555arx ; real_T bzgg0ulu4k ; real_T bflbqg5zak ; real_T
jsagt0mcn5 ; real_T ocdgy2ejgh ; real_T d5dnpexn4t ; real_T ovli05n5nk ;
real_T nwecho1h3t ; real_T gnaacobfeo ; real_T ijvx2wutld ; real_T oxsptmwoac
; real_T fjr0gnghit ; real_T fdf23q01mz ; real_T d5t4jwb3c1 ; real_T
btljz0bxed ; real_T ic5zg43yv2 [ 48 ] ; real_T gsxszorohl ; real_T n2ccqijupy
; real_T mldsebqwet ; real_T e2agy2fsgi ; real_T bxhzyl4d35 ; real_T
n3egm45yhf ; real_T mrcdfgxinf ; real_T oensukc05m ; real_T pymjjsr2h5 ;
real_T l0rzxszt5j ; real_T cltyk0hpst ; real_T fy1eaz5ugh ; real_T a00pli33gs
; real_T lskivvbef2 ; real_T l2l4c054vs ; real_T cfkzncdchi ; real_T
ioiacfjeuz ; real_T ewjasibzpn ; real_T oo50ly4c1k ; real_T hchyyvnkfi ;
real_T mbrzvkgc02 ; real_T ccx5xshaae ; real_T jypsvxunzx ; real_T itef1p5z1s
; real_T pzh3uohypw ; real_T l25nn4yd54 ; real_T gpwh1wrtb0 ; real_T
g4m0cdodse ; real_T hlfbkim2ak ; real_T c1yqoeyclv ; real_T nwzdhzp3uq ;
real_T ioigirnvlb ; real_T ky1bn1pban ; real_T jwugixu4h5 ; real_T pp2zcnllgu
; real_T gqj0yx0geh ; real_T dhn2regg4c ; real_T khy3xv0wd1 ; real_T
oadqy1evwl ; real_T gvrb2v4pkg ; real_T ldh4osun4n ; real_T e4oygrgmkm ;
real_T e0maoawpyc ; real_T cofhwf5l21 ; real_T nnqsumxvpu ; real_T ajxwnd2tik
; real_T arnfohkdqn ; real_T otpvmo0dhx ; real_T pi5grrqklm [ 48 ] ; real_T
mkpq5rh3fh ; real_T iexwgqak2h ; real_T p000k5jvks ; real_T atwy10grax ;
real_T ls0ljb5vc0 ; real_T cv5uczrgts ; real_T b31300zfqr ; real_T imr3yf1vog
; real_T d3qcbjme3b ; real_T fo51whhyuk ; real_T pby3qefafo ; real_T
b40x0jqzuo ; real_T paynrqnlln ; real_T kymb1j5buj ; real_T ike0bqd0s0 ;
real_T hlc4nygesy ; real_T emx3gvk30z ; real_T j1ywojvfhu ; real_T n3nrykzbk3
; real_T hzhzx3w4rd ; real_T gxlh0er3yf ; real_T cch5sezmlj ; real_T
o0sisl31yn ; real_T nuqe21gcdg ; real_T lulptfdn2v ; real_T prxfbd5j0u ;
real_T ircuv1shpc ; real_T hc2nh4v2yq ; real_T pw5v12y3ow ; real_T jzj2j2nzgr
; real_T op0m35r3ke ; real_T cyz5kb5odh ; real_T ofwowk1umm ; real_T
hnjzpxh21j ; real_T di5wsdkn0z ; real_T id5wqm3ssr ; real_T aalyzhw4dl ;
real_T avntdifsih ; real_T gszo0jhkh2 ; real_T dmm0rk124k ; real_T maot34c00s
; real_T erwhrbhtkw ; real_T mizmowz2v4 ; real_T oyhnern4o0 ; real_T
jq5vanxa0o ; real_T gzcxn1z3ei ; real_T lunwnotl00 ; real_T pwcmhviyfa ;
real_T i0y1vzmsou [ 48 ] ; real_T ms3fqtmbzy ; real_T ksjijdxlja ; real_T
f2apxwopt1 ; real_T etw2weyjzv ; real_T bvgcgl422b ; real_T fw5jnqnayy ;
real_T ilzljrcbe2 ; real_T o2yrfk1fkj ; real_T n5eh1d0iyp ; real_T jiuto5ikn3
; real_T aqyy3dqtlg ; real_T mns4wq01ib ; real_T pszst41gj3 ; real_T
fiixtzzm4u ; real_T jnpz5olbrg ; real_T ii1dtwyfdi ; real_T bd02cblshg ;
real_T jozjyab32g ; real_T nwzgjzcd4a ; real_T cltl3pae0r ; real_T aqi0rmfy15
; real_T lqzffi3din ; real_T fr5br5u2f5 ; real_T pfuawqdjxk ; real_T
ohicqhp5c2 ; real_T br0iuhtcdf ; real_T hffi0gte1l ; real_T dsjvii2swn ;
real_T n4wqu3tvya ; real_T pkrzl4zoxn ; real_T kddkbetzaa ; real_T olll4vevqf
; real_T fitezlt4it ; real_T jtkdprrpiq ; real_T elruqhu1gw ; real_T
jun2gnnvnq ; real_T j1s41mkvck ; real_T nrmg25w4ui ; real_T enli3ifht0 ;
real_T prewidi2th ; real_T mw3gsizyzr ; real_T hqcrboufif ; real_T o3orf1lhev
; real_T babdknai5w ; real_T ivrc3b4wgo ; real_T goy21q4l3a ; real_T
ns1xz3nvrk ; real_T hjelws0phx ; real_T eq4nvgpsqt [ 48 ] ; real_T cb5bplddfd
; real_T hbrsp534bn ; real_T in1h0ego2x ; real_T p1hamuzbs1 ; real_T
a0m3ivax1i ; real_T mtbsqnucli ; real_T kyftga03p5 ; real_T mnwv2scq3z ;
real_T kxxpxhcmnt ; real_T khgoy3vcpx ; real_T gdtjfy2hjl ; real_T ddkkpvdavs
; real_T ki11dfhlp3 ; real_T b3h3updawf ; real_T psadjbwlox ; real_T
dxxsvhegqo ; real_T ixbtpgloc3 ; real_T bzufbyxjxm ; real_T jltuhbz1ng ;
real_T dfuunegyyb ; real_T hble30fuif ; real_T pebcy2vs1v ; real_T nni5thwzkt
; real_T kn3iivseuh ; real_T hkwlx4ea2v ; real_T lhbedc50xu ; real_T
glwhbxi53s ; real_T pf4zj1q4t1 ; real_T f0a4yf0lk5 ; real_T lrud1xdpjt ;
real_T ky2fvuqm1y ; real_T ley4nikp14 ; real_T n3snchwran ; real_T cxpq4nc4vn
; real_T i0sd0x2xcu ; real_T kkwqqcdfui ; real_T jexdxibumh ; real_T
gy0bpvchq3 ; real_T ouv5zxpnrj ; real_T ho5f4zeh12 ; real_T pvrg3pyvk1 ;
real_T btojk1gmmb ; real_T lscnnf54n2 ; real_T cfcgpqwr5i ; real_T hrxdp0hakn
; real_T blck5r3jjn ; real_T nfcdvdyzvx ; real_T plprg3he5c ; real_T
ajn0fnrocr [ 48 ] ; real_T ggesnqhotd ; real_T hygazcejav ; real_T dvcpuw2gcg
; real_T eyq0352y4b ; real_T fb034lljpa ; real_T ktjovoyk0g ; real_T
hpxnxzplmr ; real_T ffvwwrkkbq ; real_T bxwn3g3gd2 ; real_T lrh4dm0esj ;
real_T bo4d45gozu ; real_T eqv1b3nirq ; real_T n5sesfdozg ; real_T kfysu30hud
; real_T bghrytf3d3 ; real_T cwmmeaoh43 ; real_T ezlkzekgrb ; real_T
emmmp3iou5 ; real_T fei1k5hpwa ; real_T a20g3v5czr ; real_T hox2qskch1 ;
real_T d5vlayglg2 ; real_T iw5uxkz3im ; real_T gis5yf1fp0 ; real_T aw2tfpcqr1
; real_T cnhnznikot ; real_T brb1dhzt5b ; real_T h3sw0orbwy ; real_T
arpfqcrhaw ; real_T ouo45ol4bp ; real_T ghrxwu1hvu ; real_T h5cvkxxrx1 ;
real_T ehr3eziagk ; real_T csb33yvtf2 ; real_T dx0drx3jqi ; real_T lf5qf2q3cc
; real_T mmdvwqak4r ; real_T nixlqel1rp ; real_T l31qpehim0 ; real_T
lj44jlwn14 ; real_T o3qotdi3uh ; real_T d3d5fdshct ; real_T aenhpcucwt ;
real_T o5hdhu3lyq ; real_T hz42dhcvx3 ; real_T blk5t4lbmv ; real_T ldbihd0pay
; real_T mg3ocxel2q ; real_T js1e3qr2m1 [ 48 ] ; real_T azjmzqd3vb ; real_T
gmbaq2fbjb ; real_T h0gqs1nhdm ; real_T mjdat5hd2e ; real_T lhuj2gsrko ;
real_T kxm5w2htjt ; real_T okyxtfo4ko ; real_T bpzq12sk1y ; real_T nmztaq5xza
; real_T nmdxbbj1gj ; real_T duawl3zq0w ; real_T irqllizifh ; real_T
abcg0jvxu2 ; real_T lhv3fabtry ; real_T jagy2oxlxs ; real_T b1cj1hxqcp ;
real_T mmuxgctkpa ; real_T nhyg4avrjq ; real_T ptb4abw35t ; real_T astupp0ykj
; real_T bxevyg1qfv ; real_T bsyf5qnqlq ; real_T pqe4h0mldk ; real_T
oabhgyaqej ; real_T f30of2biun ; real_T isnln11ygz ; real_T eqca5yhlwz ;
real_T oiu1puuk0r ; real_T hpa1cu2ml4 ; real_T nonqf4a0km ; real_T n4ec24vcv4
; real_T mfnrp4nocv ; real_T prob4hxsnz ; real_T nojsqgyym0 ; real_T
gi5vxvkn1l ; real_T j1jg4ps3pb ; real_T mrb1fq2yah ; real_T f20ue4bczk ;
real_T a2ugtljmkq ; real_T gvyaxp1jds ; real_T ll0aghnbw3 ; real_T hkmm0vso4o
; real_T kcaeorhfgi ; real_T cj5l40duds ; real_T idkhic3gum ; real_T
cmcorjnw34 ; real_T eqps0gcjjy ; real_T opcvbfbu0a ; real_T k2usimljyx [ 48 ]
; real_T c5am1xxeyp ; real_T ltvkuhvonr ; real_T mrfoka5crq ; real_T
hzj3ghd3ti ; real_T kd315mesw4 ; real_T g35mjbeqs3 ; real_T dtu3mjgum2 ;
real_T oevtjor0u3 ; real_T ipjqzabc30 ; real_T oopq5yauzv ; real_T hwri03ubr2
; real_T hroaolzuga ; real_T omo0odknr4 ; real_T dawcyvu3ar ; real_T
dzqdbynuky ; real_T lgeiac2zcg ; real_T f2azip3nkv ; real_T nejc01f2yj ;
real_T exxy3crrss ; real_T mbeg3v5z5m ; real_T fu4duvs1oh ; real_T ebzmfciyvp
; real_T i0jcfar22j ; real_T bgtvlmqb0i ; real_T b2jrj4aug2 ; real_T
ikwdhesgqr ; real_T glumzkv1kv ; real_T ftjkvl0ttv ; real_T gt5qnx3oug ;
real_T fq04nnejal ; real_T nz1n2dwtmm ; real_T hcm40myr01 ; real_T hkuzgnbjbt
; real_T oi4qaxezfh ; real_T a4gf2pw04z ; real_T lluqlqnbie ; real_T
geucbkz3sb ; real_T dy5jvvwh21 ; real_T at3grkcr0i ; real_T nclby2bt4t ;
real_T cxic31gs5o ; real_T bj0j0lkfw3 ; real_T o3nf12o3kv ; real_T cb5qphbn0v
; real_T g0c4aqlyry ; real_T pwg5klf2pi ; real_T kv203gp00h ; real_T
n0yawwlhtp ; real_T n432pxj0nf [ 48 ] ; real_T gdizqui00u ; real_T iaf3qnvwai
; real_T ppwfshiqbj ; real_T dtgcbug2z1 ; real_T jajcvm3ojj ; real_T
juhelemmkf ; real_T c5k4edupr5 ; real_T fpw2s2zwfo ; real_T b3j431g3ib ;
real_T jajiwpdbda ; real_T ijqf2bh5go [ 3 ] ; real_T nqrdiqgjxm ; real_T
edbedwxht5 ; real_T ouitoiyxuf ; real_T lwwgzcjoh5 ; real_T htnfuvkgid ;
real_T gt2e0gwhn0 ; real_T kod4h1025c ; real_T gye3zy1a0f ; real_T mgmgpzdaim
; real_T kpjwqjmfqs ; real_T dv2i5nazyy ; real_T fnwh3t55no ; real_T
kawbvnvky3 ; real_T kzusmmwb1m ; real_T ppxw152mhu ; real_T lyfqv1evtf [ 3 ]
; real_T fpbsng3i4c ; real_T enkm4ifchy ; real_T bojcrrwkcj ; real_T
iu2zqirfs2 ; real_T e0xj4q2kh1 ; real_T iwlrjtti0w ; real_T l1efzgifhl ;
real_T ll3qrorekf ; real_T admbdmfv3c ; real_T h152k3wasb ; real_T lvuiwhpda4
; real_T il4x3p0kai ; } B ; typedef struct { real_T kpa0qz1w2m ; real_T
ksp1zkwcj2 ; real_T lnyxns4prr ; real_T iq0yvshwbl ; real_T hwrivx5mi4 ;
real_T nb1buv1zor ; real_T oq5hmifhxo ; real_T ms1k4m0ka3 ; real_T fb5x1hmdio
; real_T bmlwssomru [ 48 ] ; real_T l4l5iifhga ; real_T oegbozknnu ; real_T
bdlz3yfllc ; real_T nqdr1b40o2 ; real_T bpnis5nmqy ; real_T jf2kk54ldn ;
real_T kvdcvco01e ; real_T lwfztydmov ; real_T dk1lpgs41d ; real_T j3ah0j5uha
; real_T jnwgqfjczs ; real_T lztbr3et3t ; real_T ad3mgyfzte ; real_T
aircger2rx ; real_T maze5hu4ab ; real_T ihbczgg1ch ; real_T jwpobdvxh3 ;
real_T nuc12zx3mo ; real_T jz4s1v251o ; real_T mip1wd2oyv ; real_T ogqyiifq2n
; real_T o035fkrhgg ; real_T bo3uxetgss ; real_T evlwxs2e1f ; real_T
lqmt5s4eon ; struct { void * AS ; void * BS ; void * CS ; void * DS ; void *
DX_COL ; void * BD_COL ; void * TMP1 ; void * TMP2 ; void * XTMP ; void *
SWITCH_STATUS ; void * SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ;
void * USWLAST ; void * XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ;
void * IDX_SW_CHG ; void * Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW
; void * SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } lpqqjlpxt1 ; struct {
void * AS ; void * BS ; void * CS ; void * DS ; void * DX_COL ; void * BD_COL
; void * TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ; void *
SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ; void *
XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG ; void
* Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } g5a0yy0hef ; struct { void * AS
; void * BS ; void * CS ; void * DS ; void * DX_COL ; void * BD_COL ; void *
TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ; void *
SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ; void *
XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG ; void
* Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } kosaktmuhw ; struct { void * AS
; void * BS ; void * CS ; void * DS ; void * DX_COL ; void * BD_COL ; void *
TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ; void *
SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ; void *
XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG ; void
* Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } lhqp2i1wv4 ; struct { void * AS
; void * BS ; void * CS ; void * DS ; void * DX_COL ; void * BD_COL ; void *
TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ; void *
SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ; void *
XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG ; void
* Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } c0rfzt21pv ; struct { void *
LoggedData ; } nczvtjazvl ; struct { void * LoggedData ; } ddhevcuw0f ;
struct { void * LoggedData ; } eyvapocerz ; struct { void * LoggedData ; }
px5gx0ovdj ; struct { void * LoggedData ; } lueewoojur ; struct { void *
LoggedData ; } ofqo4whqqs ; struct { void * LoggedData ; } gylheu2quv ;
struct { void * LoggedData ; } if3oedzqbn ; struct { void * LoggedData ; }
lnb3lesuo3 ; struct { void * LoggedData ; } jydkx4dopc ; struct { void *
LoggedData ; } f4ppq3cqy3 ; struct { void * LoggedData ; } g1bsp2ezz4 ;
struct { void * LoggedData [ 2 ] ; } lbugxtqywx ; struct { void * LoggedData
[ 2 ] ; } n03rxcpawc ; struct { void * LoggedData ; } eosjvmtbk2 ; struct {
void * LoggedData ; } gsmvko5zz1 ; struct { void * LoggedData ; } cuayv55s4x
; struct { void * LoggedData ; } jecmukiw0b ; struct { void * LoggedData ; }
afk3rf34em ; int_T hsbrr2ooio [ 11 ] ; int_T flbghk5kdt [ 11 ] ; int_T
ls42eh4ngg [ 11 ] ; int_T os5fnp2i2r [ 11 ] ; int_T fcsz3vpkb1 [ 11 ] ;
int8_T kmqrnxxbow ; int8_T f2pl5hhy0a ; int8_T f2mbtmfzg2 ; int8_T oufwnzwkdu
; int8_T lrgpgfqgzz ; uint8_T oh13f4t51u ; uint8_T itp5tejlgk ; uint8_T
d23tl2d2xe ; uint8_T k0yugcv43d ; uint8_T fpix2rdml1 ; } DW ; typedef struct
{ rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T amps_in ;
real_T capacitance ; real_T Battery_BatType ; real_T Battery1_BatType ;
real_T Battery2_BatType ; real_T Battery_BatType_l1sun2jtvt ; real_T
Battery_BatType_cmk1pph4hu ; real_T DiscretePIDController_I ; real_T
DiscretePIDController_InitialConditionForIntegrator ; real_T
DiscretePIDController_LowerSaturationLimit ; real_T DiscretePIDController_P ;
real_T Battery_SOC ; real_T Battery1_SOC ; real_T Battery2_SOC ; real_T
Battery_SOC_doariqu25f ; real_T Battery_SOC_ijowiaqvxc ; real_T
DiscretePIDController_UpperSaturationLimit ; real_T Subsystem5_r_esr ; real_T
Subsystem1_r_esr ; real_T Subsystem2_r_esr ; real_T Subsystem_r_esr ; real_T
Subsystem8_r_esr ; real_T Subsystem5_r_esr_otnqz5ubg5 ; real_T
Subsystem1_r_esr_epp1mj5kl0 ; real_T Subsystem2_r_esr_ihzsp4i5mp ; real_T
Subsystem_r_esr_a33gf5kscd ; real_T Subsystem8_r_esr_fsgykwfdu3 ; real_T
Subsystem5_r_esr_arbsh4fv2d ; real_T Subsystem1_r_esr_ii1xxm2434 ; real_T
Subsystem2_r_esr_g3e3odzj4z ; real_T Subsystem_r_esr_gtxynyerfi ; real_T
Subsystem8_r_esr_gihueny4su ; real_T EqCircuitNetwork_r_leak ; real_T
EqCircuitNetwork1_r_leak ; real_T EqCircuitNetwork2_r_leak ; real_T
ProtectionCircuit_v_cut ; real_T ProtectionCircuit1_v_cut ; real_T
ProtectionCircuit2_v_cut ; real_T ProtectionCircuit_v_min ; real_T
ProtectionCircuit1_v_min ; real_T ProtectionCircuit2_v_min ; real_T
Saturation_UpperSat ; real_T Saturation_LowerSat ; real_T
Saturation_UpperSat_lqsamz1a2q ; real_T Saturation_LowerSat_jabf313muk ;
real_T Saturation_UpperSat_bh0lef2msr ; real_T Saturation_LowerSat_e35an2lbrt
; real_T Saturation_UpperSat_aeh1cq5q5j ; real_T
Saturation_LowerSat_lpdw4vd5ik ; real_T Saturation_UpperSat_jwiz1tvuc0 ;
real_T Saturation_LowerSat_d4iiqg5kd0 ; real_T SwitchCurrents_Value [ 4 ] ;
real_T StateSpace_DS_param [ 16 ] ; real_T Constant1_Value ; real_T
Constant_Value ; real_T itinit1_InitialCondition ; real_T R2_Gain ; real_T
Currentfilter_NumCoef ; real_T Currentfilter_DenCoef [ 2 ] ; real_T
Currentfilter_InitialStates ; real_T Constant_Value_kbhmnmnkmn ; real_T
inti_gainval ; real_T inti_UpperSat ; real_T inti_LowerSat ; real_T Gain_Gain
; real_T Constant9_Value ; real_T Constant4_Value ; real_T R3_Gain ; real_T
Constant_Value_bwxnqwdlu4 ; real_T Constant1_Value_ba5ae3pck4 ; real_T
Constant3_Value ; real_T Constant2_Value ; real_T
DiscreteTimeIntegrator_gainval ; real_T Memory2_InitialCondition ; real_T
Constant1_Value_eymbazuin1 ; real_T Constant_Value_myjwkv2xqc ; real_T
itinit1_InitialCondition_kl3ucy1541 ; real_T R2_Gain_gn2hhy35bk ; real_T
Currentfilter_NumCoef_dwkwb5rq0b ; real_T Currentfilter_DenCoef_mwjcihxo4o [
2 ] ; real_T Currentfilter_InitialStates_nr2e02qeiq ; real_T
Constant_Value_okglhro0vm ; real_T inti_gainval_pb2vhjbqxt ; real_T
inti_UpperSat_ovnl0mfsbp ; real_T inti_LowerSat_lm4gcia0l4 ; real_T
Gain_Gain_iqgvprw0ss ; real_T Constant9_Value_a5rtdjlock ; real_T
Constant4_Value_lthflsnkeu ; real_T R3_Gain_lw2doffbmz ; real_T
Constant_Value_g12zcbefww ; real_T Constant1_Value_jbvs0nsfpj ; real_T
Constant3_Value_nj5jkoby2k ; real_T Constant2_Value_gj2xaq4m3s ; real_T
DiscreteTimeIntegrator_gainval_n5xpalw41i ; real_T
Memory2_InitialCondition_pf3pych4fa ; real_T Constant1_Value_nyr1jvuern ;
real_T Constant_Value_ftfxsd2jhc ; real_T itinit1_InitialCondition_cih32wawzb
; real_T R2_Gain_dw41hzcoux ; real_T Currentfilter_NumCoef_o5cnlr2zv4 ;
real_T Currentfilter_DenCoef_pf4x0hfod2 [ 2 ] ; real_T
Currentfilter_InitialStates_kut2jdkaed ; real_T Constant_Value_l0gkldjobz ;
real_T inti_gainval_hllk4zcjzx ; real_T inti_UpperSat_fafppsy3ai ; real_T
inti_LowerSat_lfqfty24xa ; real_T Gain_Gain_obfealy1ww ; real_T
Constant9_Value_il1twk33xw ; real_T Constant4_Value_hnhj3hl1qn ; real_T
R3_Gain_ozmg2mkfqb ; real_T Constant_Value_cos31swra1 ; real_T
Constant1_Value_e05fuchp0u ; real_T Constant3_Value_hicomfdnpb ; real_T
Constant2_Value_g43qk25t5s ; real_T DiscreteTimeIntegrator_gainval_dduja0dlmp
; real_T Memory2_InitialCondition_pxnsyfial5 ; real_T StateSpace_AS_param [
2304 ] ; real_T StateSpace_BS_param [ 192 ] ; real_T StateSpace_CS_param [
9600 ] ; real_T StateSpace_DS_param_j0m4mfy5zk [ 800 ] ; real_T
StateSpace_X0_param [ 48 ] ; real_T SwitchCurrents_Value_az3dw3pjw2 [ 4 ] ;
real_T StateSpace_DS_param_iushkyjw3b [ 24 ] ; real_T
SwitchCurrents_Value_hsgedxy3pe [ 4 ] ; real_T Constant1_Value_cvafov1aay ;
real_T Constant_Value_fuqdogx424 ; real_T itinit1_InitialCondition_jvi22guyny
; real_T R2_Gain_g3s0uniddd ; real_T Currentfilter_NumCoef_cmdxxeoc5l ;
real_T Currentfilter_DenCoef_lvlptmaxwd [ 2 ] ; real_T
Currentfilter_InitialStates_mpd5odciik ; real_T Constant_Value_e2zke2vgjc ;
real_T inti_gainval_kj3rbkybv5 ; real_T inti_UpperSat_knlety0kfl ; real_T
inti_LowerSat_fqu2adq33w ; real_T Gain_Gain_i4pvr0q4al ; real_T
Constant9_Value_h31y2anloq ; real_T Constant4_Value_i0byxzx5ou ; real_T
R3_Gain_f2u242ik2e ; real_T Constant_Value_ldtorhiuhw ; real_T
Constant1_Value_k0ii2vzisz ; real_T Constant3_Value_mp2iadeyaa ; real_T
Constant2_Value_o4lojhk0zb ; real_T DiscreteTimeIntegrator_gainval_lhnmikqaol
; real_T Memory2_InitialCondition_np5byfbcx3 ; real_T
StateSpace_DS_param_gcibvrcmds [ 35 ] ; real_T
SwitchCurrents_Value_cvg54ebmbe [ 4 ] ; real_T Constant1_Value_kw1evdsdjk ;
real_T Constant_Value_kemd1naiax ; real_T itinit1_InitialCondition_ogfkm4kbb3
; real_T R2_Gain_jg254swwaz ; real_T Currentfilter_NumCoef_orciffprp3 ;
real_T Currentfilter_DenCoef_insasfptku [ 2 ] ; real_T
Currentfilter_InitialStates_jsum3iw4ku ; real_T Constant_Value_i1wr2oz2nq ;
real_T inti_gainval_osk2p2d2at ; real_T inti_UpperSat_kkiq22x4id ; real_T
inti_LowerSat_jiolab11br ; real_T Gain_Gain_pyhxvpyinf ; real_T
Constant9_Value_htg43rfxti ; real_T Constant4_Value_gu2biizajn ; real_T
R3_Gain_juiudqialo ; real_T Constant_Value_clcghdqsjf ; real_T
Constant1_Value_h5janxrbot ; real_T Constant3_Value_i0zzufmxbg ; real_T
Constant2_Value_ey2pmru5zy ; real_T DiscreteTimeIntegrator_gainval_erswkl2tg5
; real_T Memory2_InitialCondition_eimmvbkaw2 ; real_T
StateSpace_DS_param_g5puuiyo4c [ 35 ] ; real_T donotdeletethisgain_Gain ;
real_T donotdeletethisgain_Gain_obohuwjgss ; real_T
donotdeletethisgain_Gain_b1vlnha0qz ; real_T
donotdeletethisgain_Gain_nuvitn0upq ; real_T
donotdeletethisgain_Gain_lb23m0prjw ; real_T
donotdeletethisgain_Gain_m0qjxtcre2 ; real_T
donotdeletethisgain_Gain_hk5giacacu ; real_T
donotdeletethisgain_Gain_a1x2gitggu ; real_T
donotdeletethisgain_Gain_h5woy0ru3e ; real_T
donotdeletethisgain_Gain_ncd3yr52zh ; real_T
donotdeletethisgain_Gain_nn34zdc5ca ; real_T
donotdeletethisgain_Gain_nleknairzc ; real_T
donotdeletethisgain_Gain_bo5dnxkkfq ; real_T
donotdeletethisgain_Gain_b203qkt0rc ; real_T
donotdeletethisgain_Gain_j11lmxuq1s ; real_T
donotdeletethisgain_Gain_mf0bb3uaxb ; real_T
donotdeletethisgain_Gain_aludmneo2y ; real_T
donotdeletethisgain_Gain_itewz5c4d1 ; real_T
donotdeletethisgain_Gain_glgev4gucb ; real_T
donotdeletethisgain_Gain_ijcbk514vy ; real_T
donotdeletethisgain_Gain_m01b0jky3l ; real_T
donotdeletethisgain_Gain_dkdqd2msdb ; real_T
donotdeletethisgain_Gain_fxdq0uyw1l ; real_T
donotdeletethisgain_Gain_bljbittfqv ; real_T
donotdeletethisgain_Gain_hicokfbrce ; real_T
donotdeletethisgain_Gain_fa4f0n5c15 ; real_T
donotdeletethisgain_Gain_p22hoda1r3 ; real_T
donotdeletethisgain_Gain_m0v2z30bgb ; real_T
donotdeletethisgain_Gain_d4hss32n5d ; real_T
donotdeletethisgain_Gain_asas5kcfxe ; real_T
donotdeletethisgain_Gain_gey1v0mv4f ; real_T
donotdeletethisgain_Gain_ijbj54nifm ; real_T
donotdeletethisgain_Gain_abjwtqvssf ; real_T
donotdeletethisgain_Gain_axxuroz1ej ; real_T
donotdeletethisgain_Gain_o2orwmad0t ; real_T
donotdeletethisgain_Gain_ioq4qzgaou ; real_T
donotdeletethisgain_Gain_civ1ln1upa ; real_T
donotdeletethisgain_Gain_iztw4m0afw ; real_T
donotdeletethisgain_Gain_elo15k4k0d ; real_T
donotdeletethisgain_Gain_ggpg0yk2ar ; real_T
donotdeletethisgain_Gain_k2ttslk1on ; real_T
donotdeletethisgain_Gain_gwiqt05u1s ; real_T
donotdeletethisgain_Gain_oivqfecjsw ; real_T
donotdeletethisgain_Gain_bttyhm5zhc ; real_T
donotdeletethisgain_Gain_osbmxzvoso ; real_T
donotdeletethisgain_Gain_cowxgcq5gc ; real_T
donotdeletethisgain_Gain_cgwizosgxb ; real_T
donotdeletethisgain_Gain_mhqlonzjzf ; real_T
donotdeletethisgain_Gain_g0hdv4qsoo ; real_T
donotdeletethisgain_Gain_prrv14dslb ; real_T
donotdeletethisgain_Gain_cj511fcgiy ; real_T
donotdeletethisgain_Gain_iapeycct4d ; real_T
donotdeletethisgain_Gain_phewasapsx ; real_T
donotdeletethisgain_Gain_p2oiiegygu ; real_T
donotdeletethisgain_Gain_mdyvsmyybe ; real_T
donotdeletethisgain_Gain_glew5jkhkj ; real_T
donotdeletethisgain_Gain_eimquw0n2p ; real_T
donotdeletethisgain_Gain_k220czuthw ; real_T
donotdeletethisgain_Gain_hmpecviech ; real_T
donotdeletethisgain_Gain_g5obetbnok ; real_T
donotdeletethisgain_Gain_ga0dj5w1ql ; real_T
donotdeletethisgain_Gain_binafeuqjh ; real_T
donotdeletethisgain_Gain_eqrhtnxyg5 ; real_T
donotdeletethisgain_Gain_ddhdsnfkug ; real_T
donotdeletethisgain_Gain_bn45ltk4qb ; real_T
donotdeletethisgain_Gain_iuotvxc1h1 ; real_T
donotdeletethisgain_Gain_ghs3z0xmeg ; real_T
donotdeletethisgain_Gain_bhmvbvx5fo ; real_T
donotdeletethisgain_Gain_gkurugewjq ; real_T
donotdeletethisgain_Gain_enepvic532 ; real_T
donotdeletethisgain_Gain_jzbx1auamj ; real_T
donotdeletethisgain_Gain_ptpkzxubqz ; real_T
donotdeletethisgain_Gain_cbhgtkdx0m ; real_T
donotdeletethisgain_Gain_oryxavrjn3 ; real_T
donotdeletethisgain_Gain_lctmd2znr2 ; real_T
donotdeletethisgain_Gain_iglgb33y0r ; real_T
donotdeletethisgain_Gain_m1u2zjf031 ; real_T
donotdeletethisgain_Gain_noikqhsusm ; real_T
donotdeletethisgain_Gain_nx0zyith52 ; real_T
donotdeletethisgain_Gain_es5fs4t3ls ; real_T
donotdeletethisgain_Gain_p4fuoxyqti ; real_T
donotdeletethisgain_Gain_niszehu1re ; real_T
donotdeletethisgain_Gain_lokr1wckxt ; real_T
donotdeletethisgain_Gain_dlvq1s5iey ; real_T
donotdeletethisgain_Gain_jjbgw3phrs ; real_T
donotdeletethisgain_Gain_ogchx0b4dj ; real_T
donotdeletethisgain_Gain_apee1afii2 ; real_T
donotdeletethisgain_Gain_ivx4wfvg5y ; real_T
donotdeletethisgain_Gain_f1xclxcrfm ; real_T
donotdeletethisgain_Gain_ntbnnzarjw ; real_T
donotdeletethisgain_Gain_b5a0squg4y ; real_T
donotdeletethisgain_Gain_pewmpm0yk1 ; real_T
donotdeletethisgain_Gain_gre0j2jzp1 ; real_T
donotdeletethisgain_Gain_nomggwjlas ; real_T
donotdeletethisgain_Gain_dp2ym3idox ; real_T
donotdeletethisgain_Gain_bmngvaamn1 ; real_T
donotdeletethisgain_Gain_nxz1clmaov ; real_T
donotdeletethisgain_Gain_nqio443dnx ; real_T
donotdeletethisgain_Gain_kz3impy0o5 ; real_T
donotdeletethisgain_Gain_iy5t0jtjg2 ; real_T
donotdeletethisgain_Gain_kera0fgtk1 ; real_T
donotdeletethisgain_Gain_oxxk0ggwu2 ; real_T
donotdeletethisgain_Gain_leuzskterp ; real_T
donotdeletethisgain_Gain_cw3iibytty ; real_T
donotdeletethisgain_Gain_hlofkijp2p ; real_T
donotdeletethisgain_Gain_oozobhhmty ; real_T
donotdeletethisgain_Gain_kdw1ewo4sm ; real_T
donotdeletethisgain_Gain_dobwp0ddz0 ; real_T
donotdeletethisgain_Gain_hiuigxffxk ; real_T
donotdeletethisgain_Gain_d1bxizy1a0 ; real_T
donotdeletethisgain_Gain_bpkw5rvl3p ; real_T
donotdeletethisgain_Gain_nyoxhgu11x ; real_T
donotdeletethisgain_Gain_ghqxupels2 ; real_T
donotdeletethisgain_Gain_lxptv4ateq ; real_T
donotdeletethisgain_Gain_fwayzqc54u ; real_T
donotdeletethisgain_Gain_c2rwqk2pjr ; real_T
donotdeletethisgain_Gain_on2nz5fv54 ; real_T
donotdeletethisgain_Gain_mfd0iviez1 ; real_T
donotdeletethisgain_Gain_ihnlekkko4 ; real_T
donotdeletethisgain_Gain_iv3spwgekg ; real_T
donotdeletethisgain_Gain_hztrvffmsx ; real_T
donotdeletethisgain_Gain_eynhh1wids ; real_T
donotdeletethisgain_Gain_acy44eylwb ; real_T
donotdeletethisgain_Gain_isvokxvpka ; real_T
donotdeletethisgain_Gain_hqgd3vabv0 ; real_T
donotdeletethisgain_Gain_kf4vkd5oqq ; real_T
donotdeletethisgain_Gain_m5yraqgtvh ; real_T
donotdeletethisgain_Gain_ca23te02jy ; real_T
donotdeletethisgain_Gain_ctnu3dvcps ; real_T
donotdeletethisgain_Gain_oyjofy31su ; real_T
donotdeletethisgain_Gain_dpzma4udiu ; real_T
donotdeletethisgain_Gain_pw0bfnybsj ; real_T
donotdeletethisgain_Gain_dmtvaeude5 ; real_T
donotdeletethisgain_Gain_ohc5duyrhl ; real_T
donotdeletethisgain_Gain_d5clcu3gww ; real_T
donotdeletethisgain_Gain_oxehvnykg4 ; real_T
donotdeletethisgain_Gain_kxfqlmbzeu ; real_T
donotdeletethisgain_Gain_owncio2r3l ; real_T
donotdeletethisgain_Gain_buyfl2rlzd ; real_T
donotdeletethisgain_Gain_a3hhvwgdcu ; real_T
donotdeletethisgain_Gain_evjm4r4ikk ; real_T
donotdeletethisgain_Gain_kyflm2yldc ; real_T
donotdeletethisgain_Gain_eir1dm1ep1 ; real_T
donotdeletethisgain_Gain_ing3gu43ry ; real_T
donotdeletethisgain_Gain_jmsk2u03ix ; real_T
donotdeletethisgain_Gain_adtqfifx2a ; real_T
donotdeletethisgain_Gain_dkg5s5cdl2 ; real_T
donotdeletethisgain_Gain_b1nmh1io45 ; real_T
donotdeletethisgain_Gain_pcvryixazn ; real_T
donotdeletethisgain_Gain_jafdhhs0lb ; real_T
donotdeletethisgain_Gain_fi4yl500ia ; real_T
donotdeletethisgain_Gain_hrs2erwflr ; real_T
donotdeletethisgain_Gain_cloarruovm ; real_T
donotdeletethisgain_Gain_n4xqqxek55 ; real_T
donotdeletethisgain_Gain_nygb0p3yi3 ; real_T
donotdeletethisgain_Gain_hxdkmh0hey ; real_T
donotdeletethisgain_Gain_obixcn5wst ; real_T
donotdeletethisgain_Gain_g0pra3nmnu ; real_T
donotdeletethisgain_Gain_llilrh0ovw ; real_T
donotdeletethisgain_Gain_me434ppbiu ; real_T
donotdeletethisgain_Gain_n2byqwxdmv ; real_T
donotdeletethisgain_Gain_d0ci3mxljq ; real_T
donotdeletethisgain_Gain_gf5dodj4i0 ; real_T
donotdeletethisgain_Gain_b2xb3y2voo ; real_T
donotdeletethisgain_Gain_jni0gdbaox ; real_T
donotdeletethisgain_Gain_hw001uqwp1 ; real_T
donotdeletethisgain_Gain_cnu4b5znzw ; real_T
donotdeletethisgain_Gain_l05iijs0th ; real_T
donotdeletethisgain_Gain_pfe53xznqx ; real_T
donotdeletethisgain_Gain_n4drsgqyl5 ; real_T
donotdeletethisgain_Gain_ll2zr5yoca ; real_T
donotdeletethisgain_Gain_l43sbscuur ; real_T
donotdeletethisgain_Gain_nubqbodbbt ; real_T
donotdeletethisgain_Gain_gso5sj2vq2 ; real_T
donotdeletethisgain_Gain_kipk4xhyhr ; real_T
donotdeletethisgain_Gain_edeuujq0z5 ; real_T
donotdeletethisgain_Gain_ooigdqvz3e ; real_T
donotdeletethisgain_Gain_kuysd0ojq4 ; real_T
donotdeletethisgain_Gain_el1iclqdfx ; real_T
donotdeletethisgain_Gain_l2pasymtsp ; real_T
donotdeletethisgain_Gain_bbbk5pvmp5 ; real_T
donotdeletethisgain_Gain_mlf5lwjcds ; real_T
donotdeletethisgain_Gain_mc13kushyj ; real_T
donotdeletethisgain_Gain_n13y04ukvo ; real_T
donotdeletethisgain_Gain_lnieqh1p50 ; real_T
donotdeletethisgain_Gain_ab40labhkn ; real_T
donotdeletethisgain_Gain_km5wnojdkf ; real_T
donotdeletethisgain_Gain_k01w0rjihl ; real_T
donotdeletethisgain_Gain_k2buuoccz5 ; real_T
donotdeletethisgain_Gain_ombnlmn0ed ; real_T
donotdeletethisgain_Gain_kdgmvhifpu ; real_T
donotdeletethisgain_Gain_duvenjhxrn ; real_T
donotdeletethisgain_Gain_l5sxpthpku ; real_T
donotdeletethisgain_Gain_kho2ggotif ; real_T
donotdeletethisgain_Gain_nvchqkvmz2 ; real_T
donotdeletethisgain_Gain_azjczsk010 ; real_T
donotdeletethisgain_Gain_a5gf31oycn ; real_T Constant_Value_mosvjmb1hb ;
real_T Integrator_gainval ; real_T Constant_Value_fppjs3x0ea ; real_T R4_Gain
; real_T Saturation_UpperSat_l1aalue1xm ; real_T
Saturation_LowerSat_ahqe14vvdn ; real_T R4_Gain_fvualtirrk ; real_T
Saturation_UpperSat_m5wqmy2wvb ; real_T Saturation_LowerSat_hafs0jsxl2 ;
real_T R4_Gain_ngs4v0tqro ; real_T Saturation_UpperSat_inwjpiolqw ; real_T
Saturation_LowerSat_e1ft3qe2jg ; real_T donotdeletethisgain_Gain_lmp34xyxo4 ;
real_T Constant12_Value ; real_T Constant_Value_iv1x2w0vhv ; real_T
Gain4_Gain ; real_T Gain1_Gain ; real_T Gain2_Gain ; real_T R1_Gain ; real_T
donotdeletethisgain_Gain_lj1umhddk1 ; real_T Constant12_Value_plqhmhde5z ;
real_T Constant_Value_d130ln2l0i ; real_T Gain4_Gain_fg3tbxrfed ; real_T
Gain1_Gain_dkplgji4xo ; real_T Gain2_Gain_ch1egfs2zt ; real_T
R1_Gain_ay1qzu5q5s ; real_T donotdeletethisgain_Gain_fujasp51dg ; real_T
Constant12_Value_dvmlx2pkqs ; real_T Constant_Value_l5znadynca ; real_T
Gain4_Gain_bhqc4zvc0o ; real_T Gain1_Gain_fehlu53xbm ; real_T
Gain2_Gain_oua2wdl3jq ; real_T R1_Gain_m3pcmnlsvx ; real_T
donotdeletethisgain_Gain_mv43u43iy2 ; real_T
donotdeletethisgain_Gain_hjdhufs4gw ; real_T
donotdeletethisgain_Gain_fyq14ev0bb ; real_T
donotdeletethisgain_Gain_h2k1sdxt4c ; real_T RateLimiter_RisingLim ; real_T
RateLimiter_FallingLim ; real_T RateLimiter_IC ; real_T Gain2_Gain_gka1vktrhi
; real_T donotdeletethisgain_Gain_i0aw0qrr1j ; real_T
Constant12_Value_o33aovv1d2 ; real_T Constant_Value_hjzwahl0rv ; real_T
Gain4_Gain_jn3s3lqgoz ; real_T Gain1_Gain_j513dbaupl ; real_T
Gain2_Gain_ikpkbbvwrt ; real_T R1_Gain_dpwnma2t2r ; real_T
donotdeletethisgain_Gain_hxzgn03ewa ; real_T RateLimiter_RisingLim_jvhpkecggo
; real_T RateLimiter_FallingLim_d5p2achwo0 ; real_T RateLimiter_IC_eua3brkunu
; real_T Gain2_Gain_px1uc4eppw ; real_T donotdeletethisgain_Gain_fst5oafdsk ;
real_T Constant12_Value_ax3hipqz10 ; real_T Constant_Value_jhdk32vwtf ;
real_T Gain4_Gain_nsfdeivlwj ; real_T Gain1_Gain_flinnljcki ; real_T
Gain2_Gain_i0q1iceuxf ; real_T R1_Gain_i25021xdgk ; real_T
donotdeletethisgain_Gain_kuvj10tsac ; real_T RateLimiter_RisingLim_ljq2tkilib
; real_T RateLimiter_FallingLim_pojklgsdkc ; real_T RateLimiter_IC_payuy03iq3
; real_T Gain2_Gain_ginrxjfbvg ; uint8_T Gain_Gain_i0jfjlg44q ; uint8_T
Gain_Gain_fthgv1ydo1 ; uint8_T Gain1_Gain_af21rfcgee ; uint8_T
Gain_Gain_c0qmbgnxyo ; uint8_T Gain1_Gain_ktxeejomp2 ; uint8_T
Gain_Gain_k10n1oijw2 ; uint8_T Gain1_Gain_gd0jlj4aut ; } ; extern const char
* RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern DW rtDW ; extern P rtP ;
extern const rtwCAPI_ModelMappingStaticInfo *
battery_eq_circuit_pascal5_single_shot_stack_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern
const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern const int_T gblNumRootInportBlks ; extern const int_T
gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ; extern
const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [ ] ;
extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( void
) ;
#endif
