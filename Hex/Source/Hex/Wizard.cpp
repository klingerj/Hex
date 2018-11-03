#include "Wizard.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "EngineUtils.h"

// Default constructor required; if nothing chosen for some reason, choose All-Around build
AWizard::AWizard() : AWizard(WizardClass::AllAround) {}

// Sets default values
AWizard::AWizard(WizardClass className) : hasCast(false), hasCrafted(false), hasMoved(false), currentStage(AGameManager::ApplyEffects), other(nullptr), displayControls(false), charClass(className),
outgoingDamageBuff(0), incomingDamageBuff(0), outgoingAccuracyBuff(0)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// This is getting set to true for some reason?
	this->SetActorHiddenInGame(false);

	// Possession (not sure how this works with multiplayer?)
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set stats according to character class (can obviously change these as we develop combat)
	switch (className) {
		case WizardClass::AllAround:
			maxHealth = 200;
			originalSpeed = 2;
			break;
  
		case WizardClass::Tank:
			maxHealth = 300;
			originalSpeed = 1;
			break;
  
		case WizardClass::Scout:
			maxHealth = 140;
			originalSpeed = 3;
			break;
  
		case WizardClass::BuffDebuff:
			maxHealth = 160;
			originalSpeed = 2;
			break;
  
		case WizardClass::GlassCannon:
			maxHealth = 100;
			originalSpeed = 2;
			break;
  }

	health = maxHealth;
	speed = originalSpeed;
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();

}

void AWizard::spawnInvAndSpellbook() {
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		FVector spawn(100, 100, 1000);

		inventory = World->SpawnActor<AInventory>(AInventory::StaticClass(), spawn, FRotator(0.0f));
		UE_LOG(LogClass, Log, TEXT("Tried to spawn an inventory"));
		spellbook = World->SpawnActor<ASpellbook>(ASpellbook::StaticClass(), spawn, FRotator(0.0f));
		UE_LOG(LogClass, Log, TEXT("Tried to spawn a spellbook"));
		
		// Fill spellbook with appropriate starting spells
		// TODO: Finish filling in after more spells are created
		std::array<ASpell*, 5>& spellArr = spellbook->readiedSpells;
		switch (charClass) {
			// All-Around: Minor Fire Attack, ???, ???
			case WizardClass::AllAround:
				spellArr.at(0) = World->SpawnActor<AMinorFireDamage>(AMinorFireDamage::StaticClass(), spawn, FRotator(0.0f));
				break;
			// Buff/Debuff: ???, ???, ???
			case WizardClass::BuffDebuff:
				break;

			// Glass Cannon: Minor Electric Attack, ???, ???
			case WizardClass::GlassCannon:
				spellArr.at(0) = World->SpawnActor<AMinorElectricDamage>(AMinorElectricDamage::StaticClass(), spawn, FRotator(0.0f));
				break;

			// Scout: ???, ???, ???
			case WizardClass::Scout:
				break;

			// Tank: ???, ???, ???
			case WizardClass::Tank:
				break;
		}
	}
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	this->SetActorHiddenInGame(false);
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Turn phase hotkeys
	PlayerInputComponent->BindAction("Cast", EInputEvent::IE_Pressed, this, &AWizard::castSpell);
	PlayerInputComponent->BindAction("Craft", EInputEvent::IE_Pressed, this, &AWizard::craftSpell);
	PlayerInputComponent->BindAction("Move", EInputEvent::IE_Pressed, this, &AWizard::move);
	PlayerInputComponent->BindAction("EndTurn", EInputEvent::IE_Pressed, this, &AWizard::endTurn);

	// Spellcasting hotkeys
	PlayerInputComponent->BindAction("Spell1", EInputEvent::IE_Pressed, this, &AWizard::hotkeyOne);
	PlayerInputComponent->BindAction("Spell2", EInputEvent::IE_Pressed, this, &AWizard::hotkeyTwo);
	PlayerInputComponent->BindAction("Spell3", EInputEvent::IE_Pressed, this, &AWizard::hotkeyThree);
	PlayerInputComponent->BindAction("Spell4", EInputEvent::IE_Pressed, this, &AWizard::hotkeyFour);
	PlayerInputComponent->BindAction("Spell5", EInputEvent::IE_Pressed, this, &AWizard::hotkeyFive);

	// UI hotkeys
	PlayerInputComponent->BindAction("DisplayControls", EInputEvent::IE_Pressed, this, &AWizard::ToggleControlDisplay);
	PlayerInputComponent->BindAction("Spellbook", EInputEvent::IE_Pressed, this, &AWizard::showSpellbook);
	PlayerInputComponent->BindAction("Inventory", EInputEvent::IE_Pressed, this, &AWizard::showInventory);
}

/// GAMEPLAY FUNCTIONS
void AWizard::applyTileEffects() {
	// Only apply effects of the tile you start on
	if (hasMoved) {
		return;
	}

  for (TActorIterator<AHexGridTile> actorIter(GetWorld()); actorIter; ++actorIter) {
      AHexGridTile* currTile = *actorIter;
      //TileYield tileYield = currTile->hexGridTileEffect->Yield();
	  if (currTile) {
		  if (currTile->hexGridTileEffect) {

		  } else {
			  UE_LOG(LogClass, Log, TEXT(""));
		  }
	  } else {
		  UE_LOG(LogClass, Log, TEXT("currtile was null"));
	  }
      AResource* res = currTile->hexGridTileEffect->resource;
      inventory->addResources(res->getID());
  }

	// Apply current tile's effects and collect resources
	currentStage = AGameManager::TurnStage::ApplyEffects;
}

void AWizard::castSpell() {
	if (this != gm->turnPlayer) {
		gm->turnPlayer->castSpell();
		return;
	}

	// Can't cast if you craft; can only cast once per turn

	if (hasCrafted || hasCast) {
		return;
	}

	UE_LOG(LogClass, Log, TEXT("CAST"));

	// Cast something (handled in spell hotkey functions below)
    // Flow: Press C to enter cast mode, currentStage becomes Cast, press hotkey to cast desired spell

	currentStage = AGameManager::TurnStage::Cast;
}

void AWizard::craftSpell() {
	if (this != gm->turnPlayer) {
		gm->turnPlayer->craftSpell();
		return;
	}
	// Can't craft if you casted; can only craft once per turn
	if (hasCast || hasCrafted) {
		return;
	}

	UE_LOG(LogClass, Log, TEXT("CRAFT"));

	// Craft something
	// TODO: spellbook->modifyExistingSpell(inventory, selectedResource, selectedSpell); need to prompt for selectedResource and selectedSpell

	hasCrafted = true;
	currentStage = AGameManager::TurnStage::Craft;
}

void AWizard::move() {
	if (this != gm->turnPlayer) {
		gm->turnPlayer->move();
		return;
	}
	// Can only move once per turn
	if (hasMoved) {
		return;
	}

	UE_LOG(LogClass, Log, TEXT("MOVE"));

	// Move to selected tile

	hasMoved = true;
	currentStage = AGameManager::TurnStage::Move;
}

void AWizard::endTurn() {
	if (this != gm->turnPlayer) {
		gm->turnPlayer->endTurn();
		return;
	}
	// Reset all turn-dependent state variables
	hasCast = false;
	hasCrafted = false;
	hasMoved = false;

	UE_LOG(LogClass, Log, TEXT("END"));

	currentStage = AGameManager::TurnStage::End;
}

int AWizard::GetHealth() const {
    return health;
}


/// UI HOTKEY FUNCTIONS
void AWizard::ToggleControlDisplay() {
    if (this == gm->turnPlayer) {
        displayControls = !displayControls;
    } else {
        other->ToggleControlDisplay();
    }
}

// TODO: @Spencer, this is currently bugged in that it attempts to access a protected memory address (and it's also basic/boring). 
//		Can you make a clickable inventory UI and have this function bring it up? Right now, this function is bound to the B key.
void AWizard::showInventory() {
    FText header = FText::FromString("INVENTORY");
    std::string contents = "";

    for (int i = 0; i < inventory->inventory.size(); ++i) {
        int quant = inventory->inventory.at(i);
        switch (i) {
        case 0:
            contents += "Minor Accuracy Increase x " + std::to_string(quant) + "\n\t" + "Increase next spell's accuracy by 5%" + "\n\n";
            break;
        case 1:
            contents += "Major Accuracy Increase x " + std::to_string(quant) + "\n\t" + "Increase next spell's accuracy by 15%" + "\n\n";
            break;
        case 2:
            contents += "Minor Damage Boost x " + std::to_string(quant) + "\n\t" + "Increase next spell's damage by 10" + "\n\n";
            break;
        case 3:
            contents += "Major Damage Boost x " + std::to_string(quant) + "\n\t" + "Increase next spell's damage by 30" + "\n\n";
            break;
        }
    }

    FString fContents = contents.c_str();
    FMessageDialog::Debugf(FText::FromString(fContents), &header);
}

// TODO: @Spencer, this is probably also bugged like the inventory function, but I haven't tested it. 
//		Can you make a spell bar UI that sits at the bottom of the screen (similar to the one in League) and shows icons (if it's not too hard)
//		of what spells are ready and which key (1-5) they're bound to?
void AWizard::showSpellbook() {
	FText header = FText::FromString("SPELLBOOK");
	std::string contents = "";

	for (int i = 0; i < 5; ++i) {
		ASpell* s = spellbook->readiedSpells.at(i);
		contents += "Slot " + std::to_string(i) + ": " + s->name + "\n\t" + s->description + "\n\n";
	}

	FString fContents = contents.c_str();
	FMessageDialog::Debugf(FText::FromString(fContents), &header);
}

bool AWizard::GetDisplayControls() {
    return displayControls;
}

/// SPELL HOTKEY FUNCTIONS
void AWizard::hotkeyOne() {
	if (hasCast || hasCrafted || currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	hasCast = true;
}

void AWizard::hotkeyTwo() {
	if (hasCast || hasCrafted || currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

  hasCast = true;
}

void AWizard::hotkeyThree() {
	if (hasCast || hasCrafted || currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	hasCast = true;
}

void AWizard::hotkeyFour() {
	if (hasCast || hasCrafted || currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	hasCast = true;
}

void AWizard::hotkeyFive() {
	if (hasCast || hasCrafted || currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	hasCast = true;
}

// TODO: @Joe, did you want these done specifically as 5 separate functions? If not, we should probably condense them into one function that takes an argument since they all do the same thing
void AWizard::spellOne() {
	SpellResult r = spellbook->readiedSpells.at(0)->cast();
	other->health -= std::get<0>(r);
	this->outgoingAccuracyBuff = std::get<1>(r);
	this->incomingDamageBuff = std::get<2>(r);
	this->outgoingDamageBuff = std::get<3>(r);
}

void AWizard::spellTwo() {
	SpellResult r = spellbook->readiedSpells.at(1)->cast();
	other->health -= std::get<0>(r);
	this->outgoingAccuracyBuff = std::get<1>(r);
	this->incomingDamageBuff = std::get<2>(r);
	this->outgoingDamageBuff = std::get<3>(r);
}

void AWizard::spellThree() {
	SpellResult r = spellbook->readiedSpells.at(2)->cast();
	other->health -= std::get<0>(r);
	this->outgoingAccuracyBuff = std::get<1>(r);
	this->incomingDamageBuff = std::get<2>(r);
	this->outgoingDamageBuff = std::get<3>(r);
}

void AWizard::spellFour() {
	SpellResult r = spellbook->readiedSpells.at(3)->cast();
	other->health -= std::get<0>(r);
	this->outgoingAccuracyBuff = std::get<1>(r);
	this->incomingDamageBuff = std::get<2>(r);
	this->outgoingDamageBuff = std::get<3>(r);
}

void AWizard::spellFive() {
	SpellResult r = spellbook->readiedSpells.at(4)->cast();
	other->health -= std::get<0>(r);
	this->outgoingAccuracyBuff = std::get<1>(r);
	this->incomingDamageBuff = std::get<2>(r);
	this->outgoingDamageBuff = std::get<3>(r);
}