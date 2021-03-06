#include "cashierModule.h"

void cashierMenu(list<Book>& bookList, AvlTree& bookTree)
{

  int selection = 0;
  list<Book> shoppingCart;
  bool isComplete = false;



  do
  {
    time_t now = time(0);
    char*dt = ctime(&now);


    system("clear");

    cout << "Serendipity Book Sellers" << endl;
    cout << "Date and Time: " << dt << endl;
    cout << endl << endl;


    cout << "*            Cashier Menu            *" << endl;
    cout << "**************************************" << endl;
    cout << "* 1. Add Book To Cart                *" << endl;
    cout << "* 2. Remove Book From Cart           *" << endl;
    cout << "* 3. Proceed To Check Out            *" << endl;
    cout << "* 4. Return to Main Menu             *" << endl;
    cout << "**************************************" << endl;
    cout << endl << endl << endl << endl;


    cout << "<<                   Current Items in Cart                     >>" << endl;
    cout << "*****************************************************************" << endl;
    printCartItems(bookList, bookTree, shoppingCart);
    cout << endl << endl << endl;

    cout << "Enter Selection: ";
    cin >> selection;

    while (selection < 1 || selection > 5 || cin.fail())
    {
      cin.clear();
      cin.ignore(1000, '\n');

      cout << "Please Enter Selection (1 - 5): ";
      cin >> selection;

    }


    switch (selection)
    {
      case 1:
        addBookToCart(bookList, bookTree, shoppingCart);
        break;

      case 2:
        removeBookFromCart(bookList, bookTree, shoppingCart);
        break;

      case 3:
        isComplete = checkOutCart(bookList, bookTree, shoppingCart);
        if (isComplete)
        {
          selection = 4;
        }
        break;

      case 4:
        cout << "Returning to Main Menu" << endl;
        break;

      default:
        cout << "Something went wrong" << endl;
    }








  } while (selection != 4);



  cin.ignore(1000, '\n');
  cin.get();

}




void addBookToCart(list<Book>& bookList, AvlTree& bookTree, list<Book>& shoppingCart)
{
  int quantityToPurchase = 0;


  list<Book>::iterator it;
  int qtyAlreadyInCart = 0;

  Book* tempBook;


  tempBook = searchBook(bookList, bookTree);



  if (tempBook == nullptr)
  {
    cout << "Book Was Not Found" << endl;
    return;
  }



  if (!shoppingCart.empty())
  {
    for (it = shoppingCart.begin(); it != shoppingCart.end(); ++it)
    {
      if (*tempBook == *it)
      {
        qtyAlreadyInCart += it->getQuantityOnHand();
      }
    }
  }


  cout << endl << endl;
  cout << "Quantity Currently In Cart: " << qtyAlreadyInCart << endl;

  if (quantityToPurchase + qtyAlreadyInCart == tempBook->getQuantityOnHand())
  {
    cout << "The Mazimum Available Quantity Is Already In Cart" << endl;
    quantityToPurchase = 0;
  }
  else
  {
    cout << "Enter quanity to purchase: ";
    cin >> quantityToPurchase;

    while (cin.fail() || quantityToPurchase < 0 || (quantityToPurchase + qtyAlreadyInCart > tempBook->getQuantityOnHand()))
    {
      cin.clear();
      cin.ignore(1000, '\n');

      cout << "Quantity to purchase is not available." << endl;
      cout << "Please enter a valid quantity: ";
      cin >> quantityToPurchase;
    }

  }




  tempBook->setQuantityOnHand(quantityToPurchase);
  shoppingCart.push_back(*tempBook);
  delete tempBook;


  cout << "Please Press Enter To Continue..." << endl;

  cin.ignore(1000, '\n');
  cin.get();
}











void removeBookFromCart(list<Book>& bookList, AvlTree& bookTree, list<Book>& shoppingCart)
{

  list<Book>::iterator it;
  int selection = 0;

  system("clear");


  cout << "                       Remove Book From Cart                             " << endl;
  cout << "*************************************************************************" << endl;
  printCartItems(bookList, bookTree, shoppingCart);
  cout << " " << shoppingCart.size() + 1 <<  ". Return to Cashier Menu...";

  if (shoppingCart.empty())
  {
    return;
  }

  cout << endl << endl;
  cout << "Enter Selection to Remove from Cart: ";
  cin >> selection;

  while (selection < 1 || selection > shoppingCart.size() + 1 || cin.fail())
  {
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Pleae Enter Selection: ";
    cin >> selection;
  }

  if (selection == shoppingCart.size() + 1)
  {
    return;
  }


  int counter = 1;

  for (it = shoppingCart.begin(); it != shoppingCart.end(); ++it)
  {
    if (counter == selection)
    {
      //cout << it->getBookTitle() << endl;
      shoppingCart.remove(*it);
      break;
    }
    counter++;
  }

  cout << "Book Removed!" << endl;
  cin.ignore(1000, '\n');
  cin.get();

}





bool checkOutCart(list<Book>& bookList, AvlTree& bookTree, list<Book>& shoppingCart)
{
  time_t now = time(0);
  char*dt = ctime(&now);

  list<Book>::iterator it;
  char proceedCheckOut;
  double subTotal = 0;
  double tax = 0.075;
  double grandTotal = 0;
  bool isComplete = false;

  system("clear");

  cout << "Serendipity Book Sellers" << endl;

  cout << endl << endl;

  cout << "                             Check Out                                     " << dt;
  cout << "***************************************************************************************************" << endl;

  cout << left << setw(45) << "Book Title" << right << setw(21) << "Price" << setw(10) << "Qty" << setw(23) << "Total" << endl;
  cout << endl << endl;

  for (it = shoppingCart.begin(); it != shoppingCart.end(); it++)
  {
    cout << fixed << setprecision(2);
    cout << left << setw(45) << it->getBookTitle().substr(0, 40) << right <<  setw(15) << "$ " << setw(7) << it->getRetailPrice() << setw(10) << it->getQuantityOnHand()
        << setw(15) << "$ " << setw(7) << (it->getRetailPrice() * it->getQuantityOnHand()) << endl;

    subTotal += (it->getRetailPrice() * it->getQuantityOnHand());
  }
  cout << endl;
  cout << right << setw(99) << "------------------------------------------" << endl;

  grandTotal = subTotal + (tax * subTotal);
  cout << setw(92) << "Sub Total:  $ " << setw(7) << subTotal << endl;
  cout << setw(92) << "Tax:  $ " << setw(7) << tax * subTotal << endl;
  cout << setw(92) << "Grand Total:  $ " << setw(7) << grandTotal << endl;

  cout << endl << endl << endl << endl << endl;

  do
  {
    cout << endl;
    cout << "Proceed To Check Out? (Y/N): ";
    cin >> proceedCheckOut;
  } while (proceedCheckOut != 'y' && proceedCheckOut != 'Y' && proceedCheckOut != 'n' && proceedCheckOut != 'N');


  if (proceedCheckOut == 'y' || proceedCheckOut == 'Y')
  {
    completeTransaction(bookList, bookTree, shoppingCart);
    cout << "Transaction Completed!" << endl;
    isComplete = true;
  }


  shoppingCart.clear();

  cout << "Please Press Enter To Continue..." << endl;
  cin.ignore(1000, '\n');
  cin.get();


  return isComplete;
}



void printCartItems(list<Book>& bookList, AvlTree& bookTree, list<Book>& shoppingCart)
{
  list<Book>::iterator it;
  int counter = 1;

  if (shoppingCart.empty())
  {
    cout << "Cart is Empty" << endl;
    return;
  }


  for (it = shoppingCart.begin(); it != shoppingCart.end(); ++it)
  {

    cout << " " << counter << ". " << left << setw(35) << it->getBookTitle().substr(0, 30) << right << setw(20) << "Qty:"  << setw(5) << it->getQuantityOnHand() << endl;
    counter++;
  }

}


void completeTransaction(list<Book>& bookList, AvlTree& bookTree, list<Book>& shoppingCart)
{
  list<Book>::iterator itCart;

  list<Book>::iterator itInventory;

  for (itCart = shoppingCart.begin(); itCart != shoppingCart.end(); ++itCart)
  {
    for (itInventory = bookList.begin(); itInventory != bookList.end(); ++itInventory)
    {
      if (*itCart == *itInventory)
      {
        int qty = itInventory->getQuantityOnHand() - itCart->getQuantityOnHand();
        itInventory->setQuantityOnHand(qty);
      }

    }
  }

}
