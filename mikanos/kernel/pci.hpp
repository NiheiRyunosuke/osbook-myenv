/** @brief CONFIG_ADDRESS レジスタのIO ポートアドレス */
const uint16_t kConfigAddress = 0x0cf8;
/** @brief CONFIG_DATA レジスタのIO ポートアドレス */
const uint16_t kConfigData = 0x0cfc;

/** @brief ScanAllBus() により発見された PCI デバイスの一覧 */
inline std::array<Device, 32> device;
/** @brief devices の有効な要素の数 */
inline int num_device;
/** @brief PCI デバイスをすべて探索し devices に格納する
 * 
 * バス 0 から再帰的に PCI デバイスを探索し、devices の先頭から詰めて書き込む.
 * 発見したデバイスの数を num_devices に設定する
 */
Error ScanAllBus();