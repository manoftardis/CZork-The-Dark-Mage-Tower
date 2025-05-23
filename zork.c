#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "room.h"
#include "object.h"
#include "player.h"
#include "door.h"
#include "utility.h"

//escape characters: \033 for \e

/*
    Colors table
    ---------------
    | code | color|
    |
    |
    |
    |
    ---------------
 */


void start(void);
void createRooms(void);
void spawnPlayer(void);
void getInput();

char InputBuffer[256];

Room* startRoom;
ObjectContainer* inventory;
Player* player;

unsigned int playing = 1;

int main()
{
    start();
}


void start()
{
    createRooms();
    printf("You awaken at the foot of Castle Ghirenthal. Mist curls around your boots and clings to the"
    " twisted vines that strangle its outer walls. The morning sun is dim, trapped behind a veil of"
    " clouds. Before you, the castle’s wooden gates creak half-open, as if the structure itself were"
    " breathing — reluctantly alive.\n"
    "The King summoned you in secret. “My daughter, Princess Lysenna, has been taken,” he"
    " whispered, his voice worn with guilt. “The Dark Mage holds her in the tower’s peak. My son..."
    " went before you. But he did not return.”\n"
    "Some say the prince was defeated. Others say he betrayed them all. But darker rumors claim"
    " he never left — that he was engulfed in the tower itself.\n"
    "Now, it's your turn. The last hope of the realm.\n"
    "You step through the gate.\n");
    spawnPlayer();
    while(playing)
    {
        getInput();
    }
}

void createRooms()
{
    Room* floor1 = initRoom("The Atrium", "The atrium is vast, echoing with the weight of centuries. Cracked stone tiles form the floor, slick"
                        " with moss. \nTwo shattered statues stand beside the entryway, their faces worn smooth by time. A"
                        " pool of brackish water reflects your image… or something close to it. For a moment, the eyes"
                        " staring back at you are not your own.\n"
                        "On the ground near the far wall, you spot something strange: a withered \033[31mbat carcass\033[0m, curled"
                        " and desiccated. It might be useful later, if you know your alchemy.\n"
                        "There are three doorways leading deeper into the tower:  \n"
                        "-  To the \033[32mnorth\033[0m, a massive \033[33miron door\033[0m blocks the path upward. A keyhole gleams in the shape"
                        " of a dragon’s eye.\n"
                        "-  To the \033[32mwest\033[0m, a \033[33mpartially shattered wooden door\033[0m hangs crookedly. Through the cracks, you"
                        " glimpse what looks like a small side-room or storage hut.\n"
                        "-  To the \033[32meast\033[0m, a \033[33mstone archway\033[0m leads into what smells like an old storeroom.\n");

    startRoom = floor1;


    Room* cabin = initRoom("The Cabin", " This room—small, square, forgotten—is cloaked in a deep, motionless dust. No windows breach its stone walls; the air tastes of iron and old wood. Tattered cloth hangs from nails like defeated banners.\n"
                        "Amidst broken crates and rotting rope, a single object gleams from atop a toppled chair: a \033[31mkey\033[0m, bronze and ornately cut, its bow shaped like a serpent biting its tail. It does not belong here. It waits.\n");
    Room* storage = initRoom("The Storage Room", "You step into the storeroom. The air grows cooler, damp. The scent of mildew and rust clings to"
                        " everything.\n"
                        "-  To the \033[32mnorth\033[0m, a stack of old \033[33mcrates\033[0m — some open, some nailed shut.\n"
                        "-  To the \033[32msouth\033[0m, a heavy wooden door covered in thick \033[33mgray fungus\033[0m and patches of hardened,"
                        " bubbling slime. It's sealed completely. Something about that growth makes your skin crawl.\n"
                        "- To the \033[32mwest\033[0m, a \033[33mwooden door\033[0m leads back to the atrium.\n");
    Room* secret1 = initRoom("Secret Room", "You walk through the dark corridor for a few minutes."
                        "The air gets colder and colder until you come across a very old wooden table, lit only by a dim candle. "
                        "On the table, there is a small \033[31mwooden chest\033[0m. You open it, and inside is a message that reads:\n\n"
                        "This tower is not just a tower. "
                        "It is something that we all have inside of us. It is the shadow that weighs on our hearts every day. "
                        "Some can bear its weight, while others are devoured by it. Whoever built this tower, has not only lost his heart, "
                        "he has lost everything that reminded him of being human. In place of a heart, he has only a chasm, panting and drooling in the darkness. "
                        "It is too late to ask if it is his fault or if he is just a victim. He must be stopped. \n\n"
                        "You who are reading this, please help me. Free me from him.\n\n"
                        "You will need another fragment to reveal the truth. To do that, you will have to \033[34mchange\033[0m and \033[34mdeceive\033[0m.\n");

    Room* floor2 = initRoom("The Statue Room", "You begin your ascent. The stairs curve tightly, the air growing colder with each step."
                        "The stone walls sweat moisture. You feel watched — not by eyes, but by something else, as if the tower"
                        " itself is aware of your presence. \n"
                        "After what feels like too long, the stairs open into a wide, circular chamber lit by dull blue"
                        " crystals embedded in the walls. \nAt the center lies a large stone platform,"
                        " ringed by six circular slots, evenly spaced in a wheel-like pattern. Each slot is marked by an empty depression,"
                        " just large enough to fit something palm-sized.\n"
                        " A single engraved arrow is etched beside the first slot — an unmistakable indication that order matters.\n"
                        "This mechanism hums faintly with dormant power. Its edges shimmer in ways your eyes can’t"
                        " track. You instinctively understand:\n \033[34msomething must be returned here.\033[0m "
                        "Etched into the stone arch above the circular device:\n\n\033[34mFirst comes the eye that dares to see,\n"
                        "Then cast thy net into the sea.\n"
                        "Inspect the hull, its hidden scar,\n"
                        "Strike swift where monsters weakest are.\n"
                        "Then creep through cracks that shadows find,\n"
                        "And last, return with truth in mind.\033[0m\n\n"
                        "At the far end: a \033[33msteel door\033[0m, this one sealed by an intricate mechanical contraption of bronze"
                        " and obsidian. Strange indentations run along its base, and the surface shimmers faintly.\n"
                        "On the sides of the room, all around you, as if forming a hexagon, are six \033[33mstatues\033[0m.\n"
                        "On the east side, three towering \033[33mstatues\033[0m line the room, each mounted on a stone base with an embedded talisman, glowing faintly with an inner light.\n\n"

                        "- A \033[33mranger\033[0m, perched atop a jagged crag, gazes across an endless horizon. His eyes seem to follow you.\n"
                            "   At the base, an ancient, skemit \033[31mLens\033[0m, which distort the light\n\n"
                        "- A \033[33mknight\033[0m, mid-strike, drives a blade beneath a monster’s exposed flank. His pose is dynamic, impossible.\n"
                            "   The blackened \033[31mFang\033[0m beneath is dulled, still stained with dry blood.\n\n"
                        "- A \033[33mmessenger\033[0m, kneeling, holds out a scroll to a distant king — or perhaps to you.\n"
                            "   A rigid wax \033[31mSeal\033[0m engraved with a real symbol, is set within the pedestal.\n\n"

                        "On the west side, Three \033[33mstatues\033[0m stand in silence:\n"
                        "- A \033[33mfisherman\033[0m, casting a net into a vast, invisible ocean. His line never ends.\n"
                            "   At his feet, a small bone \033[31mHook\033[0m curved like a bait.\n\n"
                        "- A \033[33mshipwright\033[0m, crouched beside a shattered hull, inspecting it with quiet precision.\n"
                            "   In the base lies a \033[31mShard\033[0m of a broken rudder.\n\n"
                        "- A hooded \033[33mthief\033[0m crouches before a half-open vault. The vault door is cracked, as if pried by unseen force.\n"
                            "   The slender \033[31mLockpick\033[0m lies at his feet, still slick with shadow.\n\n"

                        "Each statue feels... foreign. Not ancient, but recent, as if copied from a world beyond this one."
                        "Each base holds a glowing \033[31mtalisman\033[0m, intricately carved with runes not from this world. The talismans at their feet seem removable.\n\n");
    Room* floor3 = initRoom("The Laboratory", "As you ascend the winding staircase, the air shifts — dense with the smell of sulfur, herbs, and"
                        " burnt parchment.\n"
                        "You emerge into a wide chamber suffused with an eerie green glow. Shelves line the stone"
                        " walls, filled with dusty vials and broken glassware. The ceiling is lost in shadow, but a cold draft"
                        " creeps across the floor.\n"
                        "At the center stands a broad alchemical \033[33mworktable\033[0m, cluttered and alive with strange apparatus.\n"
                        "-  To the \033[32mwest\033[0m, a narrow wooden door, scarred by heat and stains, suggests a rarely visited storage room.\n"
                        "-  To the \033[32mnorth\033[0m lies a heavy iron door, low to the ground — but sealed from the other side. Only"
                        " a narrow crack beneath the door offers a way through.\n");
    Room* ingredient = initRoom("The Ingredient Storeroom", "You open the rune-marked side door. Inside, this narrow space seems colder — metallic, stagnant.\n"
                        "Shelves of cracked glassware and rotten herbs sag along the walls. Dust blankets everything.\n"
                        "A locked \033[33mglass cabinet\033[0m near the back displays a glinting \033[31msilvery-black hair\033[0m. The door won't "
                        "budge — but the hinges are rusted.\n"
                        "Beside a toppled cauldron, you spot a shriveled \033[31mblack root\033[0m half-buried in old powder.\n"
                        "One shelf draws your eye: a single corked \033[31mvial\033[0m, labeled only by a faded ink mark. Its contents"
                        "swirl thick and violet, corroding the glass slightly.\n"
                        "Something about it stings the nose.\n" 
                        "- To the \033[32meast\033[0m, a door leads back to the laboratory.\n");
    Room* floor4 = initRoom("The Grand Library", "As you return to full size, the narrow crack behind you vanishes into the stone wall.\n"
                        "You now stand in a vast library, its towering shelves heavy with ancient tomes, scrolls, and"
                        " loose parchments.\n"
                        "The air smells of dust and ink, but beneath that… something darker lingers.\n"
                        "Candelabras float slowly near the ceiling, casting wavering light.\n"
                        "-  To the \033[32mnorth\033[0m, an imposing arched door — flanked by carved columns — stands slightly"
                        " jar. You sense no magical lock or resistance.\n"
                        "- To the \033[32meast\033[0m and \033[32mwest\033[0m, the shelves are lined with books, some open, some closed. A few are bound in\n"
                        "“The way forward is clear… but the library seems unwilling to be ignored.”\n");
    Room* secret2 = initRoom("The Magician's Sanctum", "You descend into a dimly lit circular chamber. The air here is cooler, imbued with old power and"
                        " secrets untold.\n"
                        "To the south, a massive ornate \033[33mmirror\033[0m dominates the wall — its surface is cloudy and shifts"
                        " like fog. You feel watched.\n"
                        "To the \033[32mnorth\033[0m, a writing \033[33mdesk\033[0m, cluttered with notes, sealed scrolls, and a cracked inkpot. A"
                        " single book lies open: a leather-bound \033[33mdiary\033[0m with a silver emblem on its cover.\n"
                        "This room hums with residual magic — heavy, as if the magician still lingers.\n");
    Room* secret3 = initRoom("The void","As if you were the prince, you continue to walk through the path of pale, cold flames. Even with"
                        "the small amount of light these eerie flames provide, this place seems to come from the coldest"
                        "and most tormented part of the tower."
                        "At first, you only hear the echo of your footsteps as you continue to advance, then you hear"
                        "whispers that are increasingly insistent:"
                        "No one can tell you what to do. Do they think they know what's right or what's best for you?"
                        "\"What do they know about what you've been through? Prove them wrong.\"\n\"They should all bow...\"\n"
                        "If they knew how dangerous you are, then maybe they'd stop treating you like just another worm."
                        "Before they make your head explode, you close your eyes and try to concentrate. Suddenly"
                        "they stop. When you open your eyes again, you have in front of you a small glass table, on it a"
                        "cylindrical mechanism and several torn pages. The first one reads:"
                        "I knew that the prince did not have a good relationship with his father. The King beat him and"
                        "mistreated him and then treated him perhaps too kindly, turning a blind eye to deviant and"
                        "aggressive behavior."
                        "Then it was my turn to be his victim, I had been the target of his very annoying jokes and other"
                        "types of annoyances for years. This time, however, he decided to cross the line. He..."
                        "The second fragment reads:"
                        "\"The old hero, the one who preceded you, was killed by the prince. He was the first of the court"
                        "to die. The Prince managed to hide his misdeed before the King or anyone else found out. But I"
                        "knew that the old hero would never resort to such an act. I know for a fact that it was him."
                        "Now you have all the pieces to solve this mystery. Be careful though, he will find you."
                        "You must be ready.\"\n");
    Room* boss = initRoom("The Mage's Chamber", "You ascend the final spiral staircase. The air grows heavier with each step, filled with the scent"
                    " of sulfur and old incense.\n"
                    " The fifth floor opens into a vast chamber, veiled in crimson drapes and black marble. Sigils"
                    " writhe across the walls, glowing faintly as if whispering curses. At the far end of the hall,behind"
                    " a veil of shadow and shimmering arcane light… stands the Princess, locked in a prism of"
                    " magic.\n"
                    "“Please-” her voice cuts through the dark, “Help me... before he returns.”"
                    " But before you can move, the shadows twist and surge into a humanoid form: the Dark"
                    " Prince, cloaked in flowing black robes, his eyes two coals of burning malice."
                    " “You’ve come far,” he growls. “But this tower is mine. She is mine.”"
                    " He lifts a hand, and the very air cracks with power. The final battle begins.");

    //create doors and connect the rooms

    Door* iron_door = doorInit("Iron Door", "A thick iron door bars the way north. The metal is etched with symbols long since faded —"
                            " perhaps protective runes, now powerless. The keyhole is oddly shaped, like a dragon’s slit-"
                            "pupil. You try to push the door, but it doesn’t budge. You will need to find the key.\n", floor1, floor2, 0);

    floor1->north = iron_door;
    floor2->south = iron_door;

    Door* broken_door = doorInit("Broken Door", "This wooden door has suffered — splintered and barely hanging by one hinge. It's been forced"
                        " open before, but now wooden planks have been nailed haphazardly across it from the outside.\n"
                        "*Peering through the gaps, you glimpse a **dusty cabin interior**. On the floor, something glints… a **key** perhaps?\n"
                        "You’ll need something to pry these boards loose.*", floor1, cabin, 0 );

    floor1->west = broken_door;
    cabin->east = broken_door;

    Door* east_door = doorInit("Storeroom Door", "A normal door leading to a storeroom", floor1, storage, 1);

    floor1->east = east_door;
    storage->west = east_door;

    Door* sealed_door = doorInit("Sealed Door", "The southern door is unlike the others. It pulses faintly under a layer of yellowed mold and"
                            " sticky fungal growth. A foul, sour stench leaks from the seams, and touching it bare-handed"
                            " burns slightly.\n"
                            "The door cannot be opened by force. You’ll need something corrosive — a potent alchemical"
                            "concoction that can burn through the organic blockade.",storage, secret1, 0);

    storage->south = sealed_door;
    secret1->north = sealed_door;

    Door* obsidian_door = doorInit("Obsidian Door", "A door sealed by an intricate mechanical contraption of bronze"
                            " and obsidian. Strange indentations run along its base, and the surface shimmers faintly.", floor2, floor3, 0);

    floor2->north = obsidian_door;
    floor3->south = obsidian_door;

    Door* ingredient_door = doorInit("Ingredient Door", "A simple door leading to the ingredient storeroom", floor3, ingredient, 1);

    floor3->west = ingredient_door;
    ingredient->east = ingredient_door;

    Door* thick_door = doorInit("Thick Iron Door", "A thick iron door blocks your way to the next level. It has no knob, only a solid bar on the other"
                            " side — unreachable from here.\n"
                            "But there, at the bottom — a slim crack, just wide enough for a hand. If only you were much smaller…"
                            " “The door is sealed tight — but the crack beneath it might fit a creature the size of a rat.”", floor3, floor4, 0);
    //one way door
    floor3->north = thick_door;
    floor4->south = thick_door;

    Door* secret_door = doorInit("Suspicious Library","To the west, a curved shelf juts out slightly from the wall, misaligned with the others. The books here are mostly fakes — carved blocks or unreadable bindings.\n"
        "One title catches your attention:\n\n >“On the Nature of Deceive” - a worn \033[31mgreen tome\033[0m with no author.\n"
        "The spine glows faintly in the candlelight. Unlike the others, this book seems... loose.", floor4, secret2, 0);

    floor4->west = secret_door;
    secret2->east = secret_door;

    Door* mirror_door = doorInit("Mirror","The tall mirror towers over you. Its frame is carved from obsidian and bone, twisting with glyphs"
                            " that seem to move when not watched.\n"
                            "Your reflection appears murky, distant — unrecognized. You feel a quiet resistance, as if"
                            " something inside denies your presence. A whisper forms in your mind:\n"
                            "“You are not the one who bound me.”\n"
                            "The mirror will not open to your current form.\n"
                            "Only a master of dark magic — \033[35min his own image\033[0m — may command it.\n\n", secret2, secret3, 0);

    secret2->south = mirror_door;
    secret3->north = mirror_door;

    Door* arched_door = doorInit("Arched Door", "An imposing arched door — flanked by carved columns", floor4, boss, 1);

    floor4->north = arched_door;

    //create the object containers

    inventory = containerInit();

    ObjectContainer* floor1_c = containerInit();
    ObjectContainer* storeroom_c = containerInit();
    ObjectContainer* secret1_c = containerInit();
    ObjectContainer* cabin_c = containerInit();
    ObjectContainer* floor2_c = containerInit();
    ObjectContainer* statue_c = containerInit();
    ObjectContainer* alchemy_c = containerInit();
    ObjectContainer* ingredient_c = containerInit();
    ObjectContainer* library_c = containerInit();
    ObjectContainer* secret2_c = containerInit();
    ObjectContainer* secret3_c = containerInit();


    //create the objects
        //atrium

    Object* bat = objectInit("Bat Carcass", "The crumpled remains of a bat — wings shriveled, fur stiff, but faintly magical..\n",
                            0, 0, 1, 0);

        //store room
    Object* crates = objectInit("Crates", "Most of the crates are filled with rotted linens, rusted nails, and broken tools. But in one —"
                            " buried beneath a moldy burlap sack — you uncover a rusted \033[31mcrowbar\033[0m. Its grip is worn, but the"
                            " iron is solid enough.",0,0,0,0);

    Object* crowbar = objectInit("Crowbar","A rusted crowbar, heavy and stained. Still sturdy enough to pry open secrets."
                                " What if the rust was...dried blood?", 0,0,1,1);

    Object* key = objectInit("Key", "A bronze key, ornately cut. Its bow is shaped like a serpent biting its tail. You can now open the iron door on the first floor.\n",0,0,1,1);

        //statue room

    Object* lens = objectInit("Lens", "A warped glass lens, warm to the touch. Taken from the watchful ranger statue.",0,0,1,0);
    Object* hook = objectInit("Hook", "A bone-crafted hook, deceptively light. Claimed from the ever-casting fisherman.",0,0,1,0);
    Object* shard = objectInit("Shard", "A jagged rudder shard, still reflecting the shipwright’s silent scrutiny.",0,0,1,0);
    Object* fang = objectInit("Fang", "A beast’s fang, dark and dulled. Plucked from the fearless knight’s strike.",0,0,1,0);
    Object* lockpick = objectInit("Lockpick", "A slender lockpick, dark and well-worn. Found near the thief and his broken vault.",0,0,1,0);
    Object* seal = objectInit("Seal", "A red wax seal, unbroken. Taken from the kneeling messenger’s offering",0,0,1,0);

        //Alchemy room
    Object* worktable = objectInit("Worktable","The alchemical workbench is a mess of tubing, decanters, ink-splotched pages, and melted"
                            "candlewax.\n"
                            "Most is useless — ancient scribbles, burned-out beakers — but two items stand out:\n"
                            "-  A functional \033[31malembic\033[0m, cleaned and cool, sits ready for use.\n"
                            "-  An open \033[33malchemy tome\033[0m, its ribbon marking a yellowed page\n"
                            "Among the chaos lies a jar of \033[31mdried glimmerleaf\033[0m — a known alchemical catalyst.\n"
                            "There's also a small note, near the tome, that says:\n"
                            " Tricks and traps are the only way for wizards to be strong and powerful. Without them, they"
                            " are just weak. This is a hard truth, and the first lesson every wizard learns. This power is"
                            " dangerous, for without wisdom it can make a wizard a deceiver.",0,0,0,0);

    Object* alembic = objectInit("Alembic","A functional alembic, cleaned and cool, sits ready for use. Tubes coil like frozen serpents"
                            " around a glass heart. When ingredients are inserted, they shimmer briefly — as if the vessel"
                            " recognizes intent. A faint heat hums from the base, despite no fire being visible\n\n"
                            " \033[35m Wheneveryou are in the Alchemy room, you use the alembic to craft potions using only the combine command\033[0m.\n",0,0,0,0);
    Object* alchemy_tome = objectInit("Alchemy Tome","An open tome lies on the table, its brittle pages splayed beneath a golden ribbon. The ink is"
                            " faded in parts, but three recipes are clearly marked"
                            "Shrink Potion — “To slip where flesh should not pass.”\n"
                            "Ingredients: \033[31mGlimmerleaf\033[0m and \033[31mBlack Root\033[0m\n\n"
                            "Shapeshifting Draught — “To walk in forms untrue.”\n"
                            "Ingredients: \033[31mHair\033[0m and Withered  \033[31mBat\033[0m Wing\n\n"
                            "Corrosive Potion — No recipe remains, only a swirling violet spiral in the margin, pulsing"
                            "slightly on the page. A handwritten note beside it reads: “Color tells what the mind"
                            "forgets.”" ,0,0,0,0);
    Object* glimmerleaf = objectInit("Dried Glimmerleaf", "A sealed jar of glowing, translucent leaves. They shimmer like moonlight on water.",0,0,1,0);

        //Ingredient room
    Object* cabinet = objectInit("Glass Cabinet", "Inside the sealed display case lies a lock of \033[31msilvery-black hair\033[0m, curled unnaturally, bound with a"
                            " silk ribbon now faded.\n"
                            "It shimmers oddly in the light — almost as if caught between the shadows.\n"
                            "A note beneath the case reads only:"
                            "“That which remains when the crown is lost, and the heart turns to ash.”", 1, 0, 0, 0);
    Object* hair = objectInit("Silvery-black hair", "A single braid of hair, both regal and wild. It crackles with two natures",0,0,0,0);
    Object* vial = objectInit("Vial", "A vial filled with a swirl thick and violet", 0,0,1,1);
    Object* root = objectInit("Black root", "A twisted root, black as soot. Bitter-smelling, with cracks that bleed sap.", 0,0,1,0);

        //Library room

    Object* book_magic = objectInit("Magic Book", "The title is seared into the cover in curling silver: “Dominion Through Shadow”"
                            "Flipping it open, the pages are filled with forgotten incantations, blood-bound glyphs, and"
                            " forbidden rites.\n"
                            "You sense instinctively: \033[34myou will not survive the final confrontation without this knowledge.\033[0m”\n"
                            "You should \033[31mtake\033[0m this with you", 0, 0, 1, 0);
    Object* book_key = objectInit("Green Tome","“On the Nature of Deceive” – a worn green tome with no author.",0,0,1,1);

        //Secret chamber room

    Object* desk = objectInit("Writing Desk", "A desk cluttered with notes, scrolls. A single book lies open on it, a leather bound \033[31mdiary\033[0m with silver emblem on its cover",0,0,0,0);
    Object* diary = objectInit("Diary", "The diary's leather cover is cracked, as if touched too often by trembling hands. Engraved on"
                            " the front of the diary: Prince Aetherion Larch.. Inside, the early entries speak of affection,"
                            " admiration — obsession. He writes of the princess not as a person, but as a destiny.\n"
                            "“They kept her from me… behind marble, etiquette, and cowardice. But the tower — the"
                            " tower listens. It understands what I must become.”\n"
                            "With each page, his words spiral deeper into madness. Magic. Control. Possession masked as love \n"
                            "“She belongs in this tower. She belongs with me. I will seal the world away, and we shall"
                            " remain… forever.”\n"
                            "The final entry is smeared with dark ink — or blood — and ends abruptly.\n"
                            "“I gave everything. Even myself.”", 0,0,0,0);
        //Void room
    Object* cylinder = objectInit("Cylinder", "A small cylindrical mechanism, notched on the surface. It seems to have been intended to be used somewhere...",0,0,1,0);
    Object* chest = objectInit("Wooden Chest", "A small wooden chest. When you look at it you feel nostalgic, but also uneasy. On the right side"
                            " it has a lever and inside the chest there is a small mechanism connected to it. It doesn't seem"
                            " to work though. Maybe it needs something else?",0,0,1,0);


        //Usable Objects
    ObjectUsability* crowbar_usability = objectUsabilityInit();
    crowbar_usability->usableRoomCount = 2;
    crowbar_usability->usableRooms[0] = floor1;
    crowbar_usability->usableRooms[1] = ingredient;
    crowbar_usability->usedRoomCount = 0;
    crowbar->usability = crowbar_usability;

    ObjectUsability* key_usability = objectUsabilityInit();
    key_usability->usableRoomCount = 1;
    key_usability->usableRooms[0] = floor1;
    key_usability->usedRoomCount = 0;
    key->usability = key_usability;

    ObjectUsability* vial_usability = objectUsabilityInit();
    vial_usability->usableRoomCount = 1;
    vial_usability->usableRooms[0] = storage;
    vial_usability->usedRoomCount = 0;
    vial->usability = vial_usability;


    //fill the rooms with the objects

        //atrium

    floor1->inventory = floor1_c;
    addObject(floor1_c, bat);

        //storageroom

    storage->inventory = storeroom_c;
    addObject(storeroom_c, crates);
    addObject(storeroom_c, crowbar);

        //secret room
    secret1->inventory = secret1_c;
    addObject(secret1_c, chest);

        //cabin room
    cabin->inventory = cabin_c;
    addObject(cabin_c, key);

        //statue room

    floor2->inventory = statue_c;
    addObject(statue_c, lens);
    addObject(statue_c, hook);
    addObject(statue_c, shard);
    addObject(statue_c, fang);
    addObject(statue_c, seal);
    addObject(statue_c, lockpick);

        //alchemy room

    floor3->inventory = alchemy_c;
    addObject(alchemy_c, worktable);
    addObject(alchemy_c, alembic);
    addObject(alchemy_c, glimmerleaf);

        //ingredient room

    ingredient->inventory = ingredient_c;
    addObject(ingredient_c, cabinet);
    addObject(ingredient_c, root);
    addObject(ingredient_c, vial);
    addObject(ingredient_c, hair);

        //library room

    floor4->inventory = library_c;
    addObject(library_c, book_key);
    addObject(library_c, book_magic);

        //sanctum room
    secret2->inventory = secret2_c;
    addObject(secret2_c, desk);
    addObject(secret2_c, diary);

    secret3->inventory = secret3_c;
    addObject(secret3_c, cylinder);

}

// Returns 1 if the order is correct, 0 otherwise
int checkObjectOrder(ObjectContainer* container, const char** correctOrder, int orderCount) {
    Object* current = container->headObject;
    for (int i = 0; i < orderCount; i++) {
        if (!current || strcmp(current->name, correctOrder[i]) != 0) {
            return 0; // Order is wrong or not enough objects
        }
        current = current->nextObj;
    }
    // If there are extra objects, order is wrong
    if (current != NULL) return 0;
    return 1;
}


void spawnPlayer(void)
{
    player = playerInit(startRoom, inventory);
    Look(player);
}

void getInput()
{
    char* tmp = calloc(256, sizeof(char));
    char* command = calloc(256, sizeof(char));
    char* arg1 = calloc(256, sizeof(char));
    char* arg2 = calloc(256, sizeof(char));

    char* result = fgets(InputBuffer, 256, stdin);
    if (result != NULL)
    {
        //handle the input
        if(*result != '\0' && *result != EOF && *result != '\n')
        {
            while(isspace(*result))
            {
                result++;
            }
            //handle command
            int i;
            for(i = 0; i < 254 && *result != '\0' && !(isspace(*result))  && *result != EOF && *result != '\n'; i++, result++)
            {
                    tmp[i] = *result;
                    tmp[i+1] = '\0';
            }
            strncpy(command, tmp, i);

            while(isspace(*result))
            {
                result++;
            }
            if( *result == '\"')
            {
                result++;
                for(i = 0; i < 254 && *result != '\0' && *result != EOF && *result != '\"' && *result != '\n'; i++, result++)
                {
                    tmp[i] = *result;
                    tmp[i+1] = '\0';
                }
            }
            else
            {
                for(i = 0; i < 254 && *result != '\0' && !(isspace(*result))  && *result != EOF && *result != '\n'; i++, result++)
                {
                    tmp[i] = *result;
                    tmp[i+1] = '\0';
                }
            }
            strncpy(arg1, tmp, i);

            while(isspace(*result))
            {
                result++;
            }

            if( *result == '\"')
            {
                result++;
                for(i = 0; i < 254 && *result != '\0' && *result != EOF && *result != '\"' && *result != '\n'; i++, result++)
                {
                    tmp[i] = *result;
                    tmp[i+1] = '\0';
                }

            }
            else
            {
                for(i = 0; i < 254 && *result != '\0' && !(isspace(*result))  && *result != EOF && *result != '\n'; i++, result++)
                {
                    tmp[i] = *result;
                    tmp[i+1] = '\0';
                }
            }
            strncpy(arg2, tmp, i);
        }
    stringToUpper(command);
    stringToUpper(arg1);
    stringToUpper(arg2);

    }
    if(strcmp(command, "MOVETO") == 0)
    {
        MoveTo(player, arg1);
    }
    else if(strcmp(command, "LOOK") == 0)
    {
        Look(player);
    }
    else if(strcmp(command, "LOOKAT") == 0)
    {
        LookAt(player, arg1);
    }
    else if(strcmp(command, "TAKE") == 0)
    {
        Take(player, arg1);
    }
    else if(strcmp(command, "COMBINE") == 0)
    {
        Combine(player, arg1, arg2);
    }
    else if(strcmp(command, "PUT") == 0)
    {
        Put(player, arg1);
    }
    else if(strcmp(command, "USE") == 0)
    {
        Use(player, arg1);
    }
    else if(strcmp(command, "INVENTORY") == 0)
    {
        Inventory(player);
    }
    else if(strcmp(command, "HELP") == 0)
    {
        Help();
    }
    else if(strcmp(command, "QUIT") == 0)
    {
        printf("Thanks for playing!\n");
        playing = 0;
        exit(0);
    }
    else
    {
        printf("%s is not a valid command \n", command);
    }

    free(command);
    free(arg1);
    free(arg2);

    return;
}