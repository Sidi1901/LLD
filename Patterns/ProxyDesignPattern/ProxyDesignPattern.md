# Proxy Design Pattern

## Core Idea

A proxy sits in front of the real object and intercepts calls. It implements the same interface, so the client doesn't know whether it's talking to the proxy or the real object.

```
Instead of:   Client → RealObject
You do:       Client → Proxy → RealObject
```

The proxy decides what to do before/after forwarding to the real object — or whether to forward at all.

---

## Types of Proxies


**Virtual Proxy** - Defers expensive creation until the object is actually needed (lazy init) |
**Protection Proxy** - Controls access based on caller permissions |
**Remote Proxy** - Represents an object in a different address space (e.g. RPC stub) |
**Caching Proxy** - Caches results to avoid repeated expensive calls |
**Logging Proxy** - Records calls transparently for auditing or debugging |

---

## Structure

```
       <<interface>>
         Subject
        + request()

    /               \
RealSubject        Proxy
+ request()      - realSubject: Subject*
                 + request()   → delegates to realSubject (after checks)
```

---

## Solutions

### Solution 1 — Virtual Proxy (lazy loading)
[Solution1.cpp](Solution1.cpp)

`ProxyImage` holds only the filename. It creates the heavyweight `RealImage` (which loads from disk) only on the first `display()` call. Subsequent calls reuse the loaded object.

```
Client → ProxyImage::display()
              ↓ (first call only)
         new RealImage → loadFromDisk()
              ↓
         realImage->display()
```

### Solution 2 — Protection Proxy (access control)
[Solution2.cpp](Solution2.cpp)

`BankAccountProxy` wraps `RealBankAccount` and checks whether the caller is the account owner before allowing `withdraw()`. Deposits are open to anyone. The real object is never exposed directly to the client.

---

## When to Use

- Object creation is expensive and may not always be needed → **Virtual Proxy**
- You need role-based or permission-based access control → **Protection Proxy**
- You want to add logging, caching, or metrics without changing the real object

## When NOT to Use

- You just need simple delegation — this is overkill
- Performance is critical and the extra layer adds unacceptable latency
