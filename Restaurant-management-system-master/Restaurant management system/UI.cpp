#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::PrintState(
    int timestep,

    LinkedQueue<Order*>& PEND_ODG,
    LinkedQueue<Order*>& PEND_ODN,
    LinkedQueue<Order*>& PEND_OT,
    LinkedQueue<Order*>& PEND_OVN,
    PEND_OVC& PEND_OVC,
    priQueue<Order*>& PEND_OVG,

    LinkedQueue<Chef*>& Free_CS,
    LinkedQueue<Chef*>& Free_CN,

    Cook_Ords& Cooking_Orders,

    LinkedQueue<Order*>& RDY_OT,
    Ready_OV& RDY_OV,
    LinkedQueue<Order*>& RDY_OD,

    priQueue<Order*>& InServ_Orders,

    LinkedQueue<Order*>& Cancelled_Orders,
    ArrayStack<Order*>& Finished_Orders,

    priQueue<Scooter*>& Free_Scooters,
    priQueue<Scooter*>& Back_Scooters,
    LinkedQueue<Scooter*>& Maint_Scooters,

    Fit_Tables& Free_Tables,
    Fit_Tables& Busy_Sharable,
    Fit_Tables& Busy_No_Share,
    LinkedQueue<Action*> Actions,
    LinkedQueue<Order*> PEND_COMBO,
    LinkedQueue<Order*>& RDY_COMBO,

    LinkedQueue<Order*>& Pending_Rescue
)
{
    std::cout << "\n==============================\n";
    std::cout << "Current Timestep: " << timestep << "\n";
    std::cout << "==============================\n\n";

    std::cout << "---------- Actions ----------\n";
    std::cout << "Actions (" << Actions.getCount() << "): ";
    Actions.Print("Actions");
    std::cout << "\n";
    std::cout << "---------- Pending Orders ----------\n";
    std::cout << "PEND_ODG (" << PEND_ODG.getCount() << "): ";
    PEND_ODG.Print("Pending_ODG");
    std::cout << "\n";

    std::cout << "PEND_ODN (" << PEND_ODN.getCount() << "): ";
    PEND_ODN.Print("Pending_ODN");
    std::cout << "\n";

    std::cout << "PEND_OT (" << PEND_OT.getCount() << "): ";
    PEND_OT.Print("Pending_OT");
    std::cout << "\n";

    std::cout << "PEND_OVN (" << PEND_OVN.getCount() << "): ";
    PEND_OVN.Print("Pending_OVN");
    std::cout << "\n";

    std::cout << "PEND_OVC (" << PEND_OVC.getCount() << "): ";
    PEND_OVC.print();
    std::cout << "\n";

    std::cout << "PEND_OVG (" << PEND_OVG.getCount() << "): ";
    PEND_OVG.print("Pending_OVG");
    std::cout << "\n\n";
    std::cout << "PEND_COMBO (" << PEND_COMBO.getCount() << "): ";
    PEND_COMBO.Print("Pending_COMBO");
    std::cout << "\n\n";

    std::cout << "---------- Free Chefs ----------\n";
    std::cout << "Free_CS (" << Free_CS.getCount() << "): ";
    Free_CS.Print("Free_CS");
    std::cout << "\n";

    std::cout << "Free_CN (" << Free_CN.getCount() << "): ";
    Free_CN.Print("Free_CN");
    std::cout << "\n\n";

    std::cout << "---------- Cooking Orders ----------\n";
    std::cout << "Cooking_Orders (" << Cooking_Orders.getCount() << "): ";
    Cooking_Orders.print();
    std::cout << "\n\n";

    std::cout << "---------- Ready Orders ----------\n";
    std::cout << "RDY_OT (" << RDY_OT.getCount() << "): ";
    RDY_OT.Print("RDY_OT");
    std::cout << "\n";

    std::cout << "RDY_OV (" << RDY_OV.getCount() << "): ";
    RDY_OV.print();
    std::cout << "\n";

    std::cout << "RDY_OD (" << RDY_OD.getCount() << "): ";
    RDY_OD.Print("RDY_OD");
    std::cout << "\n\n";

    std::cout << "RDY_COMBO (" << RDY_COMBO.getCount() << "): ";
    RDY_COMBO.Print("RDY_COMBO");
    std::cout << "\n\n";

    std::cout << "---------- In-Service Orders ----------\n";
    std::cout << "InServ_Orders (" << InServ_Orders.getCount() << "): ";
    InServ_Orders.print("InServ_Orders");
    std::cout << "\n\n";

    // This is where the Pending Rescue queue will be printed
    std::cout << "---------- Pending Rescue ----------\n";
    std::cout << "Pending_Rescue (" << Pending_Rescue.getCount() << "): ";
    Pending_Rescue.Print("Pending_Rescue");
    std::cout << "\n\n";

    std::cout << "---------- Cancelled / Finished ----------\n";
    std::cout << "Cancelled_Orders (" << Cancelled_Orders.getCount() << "): ";
    Cancelled_Orders.Print("Cancelled_Orders");
    std::cout << "\n";

    std::cout << "Finished_Orders (" << Finished_Orders.getCount() << "): ";
    Finished_Orders.print("Finished_Orders");
    std::cout << "\n\n";

    std::cout << "---------- Scooters ----------\n";
    std::cout << "Free_Scooters (" << Free_Scooters.getCount() << "): ";
    Free_Scooters.print("Free_Scooters");
    std::cout << "\n";

    std::cout << "Back_Scooters (" << Back_Scooters.getCount() << "): ";
    Back_Scooters.print("Back_Scooters");
    std::cout << "\n";

    std::cout << "Maint_Scooters (" << Maint_Scooters.getCount() << "): ";
    Maint_Scooters.Print("Maint_Scooters");
    std::cout << "\n\n";

    std::cout << "---------- Tables ----------\n";
    std::cout << "Free_Tables (" << Free_Tables.getCount() << "): ";
    Free_Tables.print();
    std::cout << "\n";

    std::cout << "Busy_Sharable (" << Busy_Sharable.getCount() << "): ";
    Busy_Sharable.print();
    std::cout << "\n";

    std::cout << "Busy_No_Share (" << Busy_No_Share.getCount() << "): ";
    Busy_No_Share.print();
    std::cout << "\n";

    std::cout << "\n========================================\n";
}