## Build command
```bash
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -S . -B build

ninja -C build
```
## Terms
### BID
- highest price someone is willing to **BUY** at
- sabse jyda boli/kharidne wala, paise dene ko ready hai
### ASK
- lowest price someone is willing to **SELL** at
-  sabse sasta bechne ko ready hai

### SPREAD
- ask - bid = spread

### Depth
                ORDER BOOK DEPTH

        BUY (BIDS)          SELL (ASKS)
        ───────────          ───────────
        Price  Qty           Price  Qty
        ₹100   500           ₹101   200
        ₹99    300           ₹102   400
        ₹98    700           ₹103   600
        ₹97    900           ₹104   800


### Order Type
#### Limit
#### Market
- Buy/Sell immediately at the best available price
#### IOC
- Immediate OR Cancel Order
- Fill now, cancel Leftover
- It fills what it CAN Insatantly
#### FOK
- Fill Or Kill
- It must fill 100% instantly
- All now ,or Nothing
#### GTC
- Good Till Cancelled
- Stay Open,Till Filled or Cancelled

#### STOP 
- STOP LOSS
- 
#### STOP LIMIT

#### ICEBERG
- Show Tip,Hide Bulk
#### POST_ONLY
- Agar order immediately match ho jayega, exchange usse cancel/reject kar sakta hai, depending on exchange rules

# TODO
- study malloc and internal working of new keyword
- virtual memory
- when heap full for a program thenn How it call OS , when OS retirn virtual occurs page fault 
- understand cache line





