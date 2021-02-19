// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ORDER_FIXGATEWAY_SERIALIZATION_H_
#define FLATBUFFERS_GENERATED_ORDER_FIXGATEWAY_SERIALIZATION_H_

#include "flatbuffers/flatbuffers.h"

namespace FixGateway {
namespace Serialization {

struct Order_FIXG_SOR;
struct Order_FIXG_SORBuilder;

struct Order_FIXG_SOR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef Order_FIXG_SORBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_USER_ID = 4,
    VT_SERVER_ID = 6,
    VT_PRICE = 8,
    VT_QTY = 10
  };
  const flatbuffers::String *user_id() const {
    return GetPointer<const flatbuffers::String *>(VT_USER_ID);
  }
  const flatbuffers::String *server_id() const {
    return GetPointer<const flatbuffers::String *>(VT_SERVER_ID);
  }
  float price() const {
    return GetField<float>(VT_PRICE, 0.0f);
  }
  float qty() const {
    return GetField<float>(VT_QTY, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_USER_ID) &&
           verifier.VerifyString(user_id()) &&
           VerifyOffset(verifier, VT_SERVER_ID) &&
           verifier.VerifyString(server_id()) &&
           VerifyField<float>(verifier, VT_PRICE) &&
           VerifyField<float>(verifier, VT_QTY) &&
           verifier.EndTable();
  }
};

struct Order_FIXG_SORBuilder {
  typedef Order_FIXG_SOR Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_user_id(flatbuffers::Offset<flatbuffers::String> user_id) {
    fbb_.AddOffset(Order_FIXG_SOR::VT_USER_ID, user_id);
  }
  void add_server_id(flatbuffers::Offset<flatbuffers::String> server_id) {
    fbb_.AddOffset(Order_FIXG_SOR::VT_SERVER_ID, server_id);
  }
  void add_price(float price) {
    fbb_.AddElement<float>(Order_FIXG_SOR::VT_PRICE, price, 0.0f);
  }
  void add_qty(float qty) {
    fbb_.AddElement<float>(Order_FIXG_SOR::VT_QTY, qty, 0.0f);
  }
  explicit Order_FIXG_SORBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Order_FIXG_SOR> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Order_FIXG_SOR>(end);
    return o;
  }
};

inline flatbuffers::Offset<Order_FIXG_SOR> CreateOrder_FIXG_SOR(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> user_id = 0,
    flatbuffers::Offset<flatbuffers::String> server_id = 0,
    float price = 0.0f,
    float qty = 0.0f) {
  Order_FIXG_SORBuilder builder_(_fbb);
  builder_.add_qty(qty);
  builder_.add_price(price);
  builder_.add_server_id(server_id);
  builder_.add_user_id(user_id);
  return builder_.Finish();
}

inline flatbuffers::Offset<Order_FIXG_SOR> CreateOrder_FIXG_SORDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *user_id = nullptr,
    const char *server_id = nullptr,
    float price = 0.0f,
    float qty = 0.0f) {
  auto user_id__ = user_id ? _fbb.CreateString(user_id) : 0;
  auto server_id__ = server_id ? _fbb.CreateString(server_id) : 0;
  return FixGateway::Serialization::CreateOrder_FIXG_SOR(
      _fbb,
      user_id__,
      server_id__,
      price,
      qty);
}

}  // namespace Serialization
}  // namespace FixGateway

#endif  // FLATBUFFERS_GENERATED_ORDER_FIXGATEWAY_SERIALIZATION_H_
