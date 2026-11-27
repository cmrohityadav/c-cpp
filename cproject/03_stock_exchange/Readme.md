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

## Memory Pool
- O(1) allocation
- O(1) deallocation
- no call to malloc or free
- cache aligned return
### Intrusive List vs Non-Intrusive List
- Intrusive list me list ka next/prev pointer actual object ke andar hota hai.
- head -> [slot 0,next] ->[slot 1,next] ->[slot 3,next] ->NULL
- Non-intrusive list me list object ke bahar ek separate node hota hai jo object ko point karta hai
```txt
- head -> [next] ->[next] ->[next] ->NULL
           |           |        |
         slot1     slot2     slot3

```
- index %n => index & (N-1)
# TODO
- study malloc and internal working of new keyword
- virtual memory
- when heap full for a program thenn How it call OS , when OS retirn virtual occurs page fault 
- understand cache line
- cache aligned return


## SPSC Queue

```txt
Thread 1 | TCP Gateway
Thread 2 | Risk Gateway
Thread 3 | Sequencer
Thread 4 | Matching
Thread 5 | Market Data
Thread 6 | Heatbeat
```
- we need Queue where producer and consumer never block each other, never call into the kernal and never touch the heap
- Each of the threads to work parallely
- Ring Buffer
- push() ->  Tail advance on push
- pop() ->  head will advance

# TODO
- 2^k , every multiple has its lowest k bits eqqual to 0;
- so remainder is exactly those k bits
- eg. number%n= number&(n-1)

- false sharing cache align between two core coherence at hardware level
- There we split into two cache align/lines
- Atomic | release |acquire |CAS

## Clocks
### Logical Time
- steady_clock -> Monotonic time measurement
- used by: sequencer,matching engine
### Real Time
- system_clock	Actual wall-clock time (date/time)
- used by: TCP gateway heartbeat supervisor,Journal flush policy

# TODO
- learn chrono lib

## Order

### Iceberg Oder

```txt
Buy 10k share at 150.25, peak 500

qty=10000 => 9500

display_qty=500 -> 500
hidden_qty=9500 -> 9000
peak_qty=500

500 share @ 150.25
Match ! 500 shares trade

- reduce qty by 500
- reduce display_qty by 500
- sees display_qty==0 ?

        - pull =min(hidden_qty,peak_qty)=min(9500,500)=500


```

# TODo
- learn trigger order, stop loss all












