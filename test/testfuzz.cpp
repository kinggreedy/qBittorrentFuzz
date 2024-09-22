#include <string>
#include <fstream>
#include <vector>

#include <cifuzz/cifuzz.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <libtorrent/bencode.hpp>
#include <libtorrent/bdecode.hpp>
#include "base/addtorrentmanager.h"
#include "base/bittorrent/infohash.h"
#include "base/bittorrent/addtorrentparams.h"
#include "base/bittorrent/session.h"
#include "base/interfaces/iapplication.h"
#include "base/net/downloadmanager.h"
#include "base/bittorrent/torrentdescriptor.h"


class MockApplication : public IApplication {
public:
    MockApplication() {}
    ~MockApplication() {}
    QString instanceName() const override { return QLatin1String("MockApp"); }
    void setInstanceName(const QString &name) override {};
    bool isFileLoggerEnabled() const override {};
    void setFileLoggerEnabled(bool value) override {};
    Path fileLoggerPath() const override {};
    void setFileLoggerPath(const Path &path) override {};
    bool isFileLoggerBackup() const override {};
    void setFileLoggerBackup(bool value) override {};
    bool isFileLoggerDeleteOld() const override {};
    void setFileLoggerDeleteOld(bool value) override {};
    int fileLoggerMaxSize() const override {};
    void setFileLoggerMaxSize(int bytes) override {};
    int fileLoggerAge() const override {};
    void setFileLoggerAge(int value) override {};
    int fileLoggerAgeType() const override {};
    void setFileLoggerAgeType(int value) override {};

    int memoryWorkingSetLimit() const override {};
    void setMemoryWorkingSetLimit(int size) override {};
    void sendTestEmail() const override {};
    AddTorrentManager *addTorrentManager() const override {};
#ifndef DISABLE_WEBUI
    WebUI *webUI() const override {};
#endif
};

// Mock BitTorrent::Session class
namespace BitTorrent {
    class MockSession : public Session {
    public:
        MockSession() {}

        Path savePath() const override {};
        void setSavePath(const Path &path) override {};
        Path downloadPath() const override {};
        void setDownloadPath(const Path &path) override {};
        bool isDownloadPathEnabled() const override {};
        void setDownloadPathEnabled(bool enabled) override {};
        QStringList categories() const override {};
        CategoryOptions categoryOptions(const QString &categoryName) const override {};
        Path categorySavePath(const QString &categoryName) const override {};
        Path categorySavePath(const QString &categoryName, const CategoryOptions &options) const override {};
        Path categoryDownloadPath(const QString &categoryName) const override {};
        Path categoryDownloadPath(const QString &categoryName, const CategoryOptions &options) const override {};
        bool addCategory(const QString &name, const CategoryOptions &options = {}) override {};
        bool editCategory(const QString &name, const CategoryOptions &options) override {};
        bool removeCategory(const QString &name) override {};
        bool isSubcategoriesEnabled() const override {};
        void setSubcategoriesEnabled(bool value) override {};
        bool useCategoryPathsInManualMode() const override {};
        void setUseCategoryPathsInManualMode(bool value) override {};

        Path suggestedSavePath(const QString &categoryName, std::optional<bool> useAutoTMM) const override {};
        Path suggestedDownloadPath(const QString &categoryName, std::optional<bool> useAutoTMM) const override {};

        TagSet tags() const override {};
        bool hasTag(const Tag &tag) const override {};
        bool addTag(const Tag &tag) override {};
        bool removeTag(const Tag &tag) override {};
        bool isAutoTMMDisabledByDefault() const override {};
        void setAutoTMMDisabledByDefault(bool value) override {};
        bool isDisableAutoTMMWhenCategoryChanged() const override {};
        void setDisableAutoTMMWhenCategoryChanged(bool value) override {};
        bool isDisableAutoTMMWhenDefaultSavePathChanged() const override {};
        void setDisableAutoTMMWhenDefaultSavePathChanged(bool value) override {};
        bool isDisableAutoTMMWhenCategorySavePathChanged() const override {};
        void setDisableAutoTMMWhenCategorySavePathChanged(bool value) override {};

        qreal globalMaxRatio() const override {};
        void setGlobalMaxRatio(qreal ratio) override {};
        int globalMaxSeedingMinutes() const override {};
        void setGlobalMaxSeedingMinutes(int minutes) override {};
        int globalMaxInactiveSeedingMinutes() const override {};
        void setGlobalMaxInactiveSeedingMinutes(int minutes) override {};
        ShareLimitAction shareLimitAction() const override {};
        void setShareLimitAction(ShareLimitAction act) override {};

        QString getDHTBootstrapNodes() const override {};
        void setDHTBootstrapNodes(const QString &nodes) override {};
        bool isDHTEnabled() const override {};
        void setDHTEnabled(bool enabled) override {};
        bool isLSDEnabled() const override {};
        void setLSDEnabled(bool enabled) override {};
        bool isPeXEnabled() const override {};
        void setPeXEnabled(bool enabled) override {};
        bool isAddTorrentToQueueTop() const override {};
        void setAddTorrentToQueueTop(bool value) override {};
        bool isAddTorrentStopped() const override {};
        void setAddTorrentStopped(bool value) override {};
        Torrent::StopCondition torrentStopCondition() const override {};
        void setTorrentStopCondition(Torrent::StopCondition stopCondition) override {};
        TorrentContentLayout torrentContentLayout() const override {};
        void setTorrentContentLayout(TorrentContentLayout value) override {};
        bool isTrackerEnabled() const override {};
        void setTrackerEnabled(bool enabled) override {};
        bool isAppendExtensionEnabled() const override {};
        void setAppendExtensionEnabled(bool enabled) override {};
        bool isUnwantedFolderEnabled() const override {};
        void setUnwantedFolderEnabled(bool enabled) override {};
        int refreshInterval() const override {};
        void setRefreshInterval(int value) override {};
        bool isPreallocationEnabled() const override {};
        void setPreallocationEnabled(bool enabled) override {};
        Path torrentExportDirectory() const override {};
        void setTorrentExportDirectory(const Path &path) override {};
        Path finishedTorrentExportDirectory() const override {};
        void setFinishedTorrentExportDirectory(const Path &path) override {};

        int globalDownloadSpeedLimit() const override {};
        void setGlobalDownloadSpeedLimit(int limit) override {};
        int globalUploadSpeedLimit() const override {};
        void setGlobalUploadSpeedLimit(int limit) override {};
        int altGlobalDownloadSpeedLimit() const override {};
        void setAltGlobalDownloadSpeedLimit(int limit) override {};
        int altGlobalUploadSpeedLimit() const override {};
        void setAltGlobalUploadSpeedLimit(int limit) override {};
        int downloadSpeedLimit() const override {};
        void setDownloadSpeedLimit(int limit) override {};
        int uploadSpeedLimit() const override {};
        void setUploadSpeedLimit(int limit) override {};
        bool isAltGlobalSpeedLimitEnabled() const override {};
        void setAltGlobalSpeedLimitEnabled(bool enabled) override {};
        bool isBandwidthSchedulerEnabled() const override {};
        void setBandwidthSchedulerEnabled(bool enabled) override {};

        bool isPerformanceWarningEnabled() const override {};
        void setPerformanceWarningEnabled(bool enable) override {};
        int saveResumeDataInterval() const override {};
        void setSaveResumeDataInterval(int value) override {};
        std::chrono::minutes saveStatisticsInterval() const override {};
        void setSaveStatisticsInterval(std::chrono::minutes value) override {};
        int shutdownTimeout() const override {};
        void setShutdownTimeout(int value) override {};
        int port() const override {};
        void setPort(int port) override {};
        bool isSSLEnabled() const override {};
        void setSSLEnabled(bool enabled) override {};
        int sslPort() const override {};
        void setSSLPort(int port) override {};
        QString networkInterface() const override {};
        void setNetworkInterface(const QString &iface) override {};
        QString networkInterfaceName() const override {};
        void setNetworkInterfaceName(const QString &name) override {};
        QString networkInterfaceAddress() const override {};
        void setNetworkInterfaceAddress(const QString &address) override {};
        int encryption() const override {};
        void setEncryption(int state) override {};
        int maxActiveCheckingTorrents() const override {};
        void setMaxActiveCheckingTorrents(int val) override {};
        bool isI2PEnabled() const override {};
        void setI2PEnabled(bool enabled) override {};
        QString I2PAddress() const override {};
        void setI2PAddress(const QString &address) override {};
        int I2PPort() const override {};
        void setI2PPort(int port) override {};
        bool I2PMixedMode() const override {};
        void setI2PMixedMode(bool enabled) override {};
        int I2PInboundQuantity() const override {};
        void setI2PInboundQuantity(int value) override {};
        int I2POutboundQuantity() const override {};
        void setI2POutboundQuantity(int value) override {};
        int I2PInboundLength() const override {};
        void setI2PInboundLength(int value) override {};
        int I2POutboundLength() const override {};
        void setI2POutboundLength(int value) override {};
        bool isProxyPeerConnectionsEnabled() const override {};
        void setProxyPeerConnectionsEnabled(bool enabled) override {};
        ChokingAlgorithm chokingAlgorithm() const override {};
        void setChokingAlgorithm(ChokingAlgorithm mode) override {};
        SeedChokingAlgorithm seedChokingAlgorithm() const override {};
        void setSeedChokingAlgorithm(SeedChokingAlgorithm mode) override {};
        bool isAddTrackersEnabled() const override {};
        void setAddTrackersEnabled(bool enabled) override {};
        QString additionalTrackers() const override {};
        void setAdditionalTrackers(const QString &trackers) override {};
        bool isIPFilteringEnabled() const override {};
        void setIPFilteringEnabled(bool enabled) override {};
        Path IPFilterFile() const override {};
        void setIPFilterFile(const Path &path) override {};
        bool announceToAllTrackers() const override {};
        void setAnnounceToAllTrackers(bool val) override {};
        bool announceToAllTiers() const override {};
        void setAnnounceToAllTiers(bool val) override {};
        int peerTurnover() const override {};
        void setPeerTurnover(int val) override {};
        int peerTurnoverCutoff() const override {};
        void setPeerTurnoverCutoff(int val) override {};
        int peerTurnoverInterval() const override {};
        void setPeerTurnoverInterval(int val) override {};
        int requestQueueSize() const override {};
        void setRequestQueueSize(int val) override {};
        int asyncIOThreads() const override {};
        void setAsyncIOThreads(int num) override {};
        int hashingThreads() const override {};
        void setHashingThreads(int num) override {};
        int filePoolSize() const override {};
        void setFilePoolSize(int size) override {};
        int checkingMemUsage() const override {};
        void setCheckingMemUsage(int size) override {};
        int diskCacheSize() const override {};
        void setDiskCacheSize(int size) override {};
        int diskCacheTTL() const override {};
        void setDiskCacheTTL(int ttl) override {};
        qint64 diskQueueSize() const override {};
        void setDiskQueueSize(qint64 size) override {};
        DiskIOType diskIOType() const override {};
        void setDiskIOType(DiskIOType type) override {};
        DiskIOReadMode diskIOReadMode() const override {};
        void setDiskIOReadMode(DiskIOReadMode mode) override {};
        DiskIOWriteMode diskIOWriteMode() const override {};
        void setDiskIOWriteMode(DiskIOWriteMode mode) override {};
        bool isCoalesceReadWriteEnabled() const override {};
        void setCoalesceReadWriteEnabled(bool enabled) override {};
        bool usePieceExtentAffinity() const override {};
        void setPieceExtentAffinity(bool enabled) override {};
        bool isSuggestModeEnabled() const override {};
        void setSuggestMode(bool mode) override {};
        int sendBufferWatermark() const override {};
        void setSendBufferWatermark(int value) override {};
        int sendBufferLowWatermark() const override {};
        void setSendBufferLowWatermark(int value) override {};
        int sendBufferWatermarkFactor() const override {};
        void setSendBufferWatermarkFactor(int value) override {};
        int connectionSpeed() const override {};
        void setConnectionSpeed(int value) override {};
        int socketSendBufferSize() const override {};
        void setSocketSendBufferSize(int value) override {};
        int socketReceiveBufferSize() const override {};
        void setSocketReceiveBufferSize(int value) override {};
        int socketBacklogSize() const override {};
        void setSocketBacklogSize(int value) override {};
        bool isAnonymousModeEnabled() const override {};
        void setAnonymousModeEnabled(bool enabled) override {};
        bool isQueueingSystemEnabled() const override {};
        void setQueueingSystemEnabled(bool enabled) override {};
        bool ignoreSlowTorrentsForQueueing() const override {};
        void setIgnoreSlowTorrentsForQueueing(bool ignore) override {};
        int downloadRateForSlowTorrents() const override {};
        void setDownloadRateForSlowTorrents(int rateInKibiBytes) override {};
        int uploadRateForSlowTorrents() const override {};
        void setUploadRateForSlowTorrents(int rateInKibiBytes) override {};
        int slowTorrentsInactivityTimer() const override {};
        void setSlowTorrentsInactivityTimer(int timeInSeconds) override {};
        int outgoingPortsMin() const override {};
        void setOutgoingPortsMin(int min) override {};
        int outgoingPortsMax() const override {};
        void setOutgoingPortsMax(int max) override {};
        int UPnPLeaseDuration() const override {};
        void setUPnPLeaseDuration(int duration) override {};
        int peerToS() const override {};
        void setPeerToS(int value) override {};
        bool ignoreLimitsOnLAN() const override {};
        void setIgnoreLimitsOnLAN(bool ignore) override {};
        bool includeOverheadInLimits() const override {};
        void setIncludeOverheadInLimits(bool include) override {};
        QString announceIP() const override {};
        void setAnnounceIP(const QString &ip) override {};
        int maxConcurrentHTTPAnnounces() const override {};
        void setMaxConcurrentHTTPAnnounces(int value) override {};
        bool isReannounceWhenAddressChangedEnabled() const override {};
        void setReannounceWhenAddressChangedEnabled(bool enabled) override {};
        void reannounceToAllTrackers() const override {};
        int stopTrackerTimeout() const override {};
        void setStopTrackerTimeout(int value) override {};
        int maxConnections() const override {};
        void setMaxConnections(int max) override {};
        int maxConnectionsPerTorrent() const override {};
        void setMaxConnectionsPerTorrent(int max) override {};
        int maxUploads() const override {};
        void setMaxUploads(int max) override {};
        int maxUploadsPerTorrent() const override {};
        void setMaxUploadsPerTorrent(int max) override {};
        int maxActiveDownloads() const override {};
        void setMaxActiveDownloads(int max) override {};
        int maxActiveUploads() const override {};
        void setMaxActiveUploads(int max) override {};
        int maxActiveTorrents() const override {};
        void setMaxActiveTorrents(int max) override {};
        BTProtocol btProtocol() const override {};
        void setBTProtocol(BTProtocol protocol) override {};
        bool isUTPRateLimited() const override {};
        void setUTPRateLimited(bool limited) override {};
        MixedModeAlgorithm utpMixedMode() const override {};
        void setUtpMixedMode(MixedModeAlgorithm mode) override {};
        bool isIDNSupportEnabled() const override {};
        void setIDNSupportEnabled(bool enabled) override {};
        bool multiConnectionsPerIpEnabled() const override {};
        void setMultiConnectionsPerIpEnabled(bool enabled) override {};
        bool validateHTTPSTrackerCertificate() const override {};
        void setValidateHTTPSTrackerCertificate(bool enabled) override {};
        bool isSSRFMitigationEnabled() const override {};
        void setSSRFMitigationEnabled(bool enabled) override {};
        bool blockPeersOnPrivilegedPorts() const override {};
        void setBlockPeersOnPrivilegedPorts(bool enabled) override {};
        bool isTrackerFilteringEnabled() const override {};
        void setTrackerFilteringEnabled(bool enabled) override {};
        bool isExcludedFileNamesEnabled() const override {};
        void setExcludedFileNamesEnabled(bool enabled) override {};
        QStringList excludedFileNames() const override {};
        void setExcludedFileNames(const QStringList &newList) override {};
        void applyFilenameFilter(const PathList &files, QList<BitTorrent::DownloadPriority> &priorities) override {};
        QStringList bannedIPs() const override {};
        void setBannedIPs(const QStringList &newList) override {};
        ResumeDataStorageType resumeDataStorageType() const override {};
        void setResumeDataStorageType(ResumeDataStorageType type) override {};
        bool isMergeTrackersEnabled() const override {};
        void setMergeTrackersEnabled(bool enabled) override {};
        bool isStartPaused() const override {};
        void setStartPaused(bool value) override {};
        TorrentContentRemoveOption torrentContentRemoveOption() const override {};
        void setTorrentContentRemoveOption(TorrentContentRemoveOption option) override {};

        bool isRestored() const override {};

        bool isPaused() const override {};
        void pause() override {};
        void resume() override {};

        Torrent *getTorrent(const TorrentID &id) const override {};
        Torrent *findTorrent(const InfoHash &infoHash) const override {};
        QList<Torrent *> torrents() const override {};
        qsizetype torrentsCount() const override {};
        const SessionStatus &status() const override {};
        const CacheStatus &cacheStatus() const override {};
        bool isListening() const override {};

        void banIP(const QString &ip) override {};

        bool isKnownTorrent(const InfoHash &infoHash) const override {};
        bool addTorrent(const TorrentDescriptor &torrentDescr, const AddTorrentParams &params = {}) override {};
        bool removeTorrent(const TorrentID &id, TorrentRemoveOption deleteOption = TorrentRemoveOption::KeepContent) override {};
        bool downloadMetadata(const TorrentDescriptor &torrentDescr) override {};
        bool cancelDownloadMetadata(const TorrentID &id) override {};

        void increaseTorrentsQueuePos(const QList<TorrentID> &ids) override {};
        void decreaseTorrentsQueuePos(const QList<TorrentID> &ids) override {};
        void topTorrentsQueuePos(const QList<TorrentID> &ids) override {};
        void bottomTorrentsQueuePos(const QList<TorrentID> &ids) override {};
    };
}

class TestAddTorrentManager : public AddTorrentManager {
public:
    TestAddTorrentManager(MockApplication *app, BitTorrent::MockSession *session)
        : AddTorrentManager(app, session) {}
    using AddTorrentManager::processTorrent;
    using AddTorrentManager::handleAddTorrentFailed;
};

FUZZ_TEST_SETUP() {
    // Perform any one-time setup required by the FUZZ_TEST function.
}

FUZZ_TEST(const uint8_t *data, size_t size) {
    // Use FuzzedDataProvider to generate random input data
    FuzzedDataProvider fuzzed_data(data, size);

    // Fuzz Torrent Parsing and P2P communication that use bdecode under the hood
    size_t random_size = fuzzed_data.ConsumeIntegralInRange<size_t>(512, 1048576); // Between 512 bytes to 1 MB
    std::string bencode_data = fuzzed_data.ConsumeRandomLengthString(random_size);
    lt::bdecode_node bencoded_entry;
    lt::error_code bencode_ec;
    lt::bdecode(bencode_data.data(), bencode_data.data() + bencode_data.size(), bencoded_entry, bencode_ec);

    // Fuzz Torrent Add Manager, responsible for adding torrent and handling Magnet
    // Re-encode the data
    std::vector<char> output;
    lt::bencode(std::back_inserter(output), bencoded_entry);

    size_t random_size_source = fuzzed_data.ConsumeIntegralInRange<size_t>(512, 1048576);
    QString source = QString::fromStdString(fuzzed_data.ConsumeRandomLengthString(random_size_source));

    // Create random AddTorrentParams
    BitTorrent::AddTorrentParams params;
    params.name = QString::fromStdString(fuzzed_data.ConsumeRandomLengthString(256));
    params.category = QString::fromStdString(fuzzed_data.ConsumeRandomLengthString(64));
    params.savePath = Path(QString::fromStdString(fuzzed_data.ConsumeRandomLengthString(512)));

    // Optional values with random assignments
    params.useDownloadPath = fuzzed_data.ConsumeBool() ? std::optional<bool>{fuzzed_data.ConsumeBool()} : std::nullopt;
    params.downloadPath = Path(QString::fromStdString(fuzzed_data.ConsumeRandomLengthString(512)));
    params.addToQueueTop = fuzzed_data.ConsumeBool() ? std::optional<bool>{fuzzed_data.ConsumeBool()} : std::nullopt;
    params.addStopped = fuzzed_data.ConsumeBool() ? std::optional<bool>{fuzzed_data.ConsumeBool()} : std::nullopt;
    params.useAutoTMM = fuzzed_data.ConsumeBool() ? std::optional<bool>{fuzzed_data.ConsumeBool()} : std::nullopt;
    params.sequential = fuzzed_data.ConsumeBool();
    params.firstLastPiecePriority = fuzzed_data.ConsumeBool();
    params.addForced = fuzzed_data.ConsumeBool();
    params.skipChecking = fuzzed_data.ConsumeBool();
    params.uploadLimit = fuzzed_data.ConsumeIntegralInRange<int>(-1, 100000);
    params.downloadLimit = fuzzed_data.ConsumeIntegralInRange<int>(-1, 100000);
    params.seedingTimeLimit = fuzzed_data.ConsumeIntegralInRange<int>(0, 1000);
    params.inactiveSeedingTimeLimit = fuzzed_data.ConsumeIntegralInRange<int>(0, 1000);
    params.ratioLimit = fuzzed_data.ConsumeFloatingPoint<qreal>();

    // Random file paths
    int numFilePaths = fuzzed_data.ConsumeIntegralInRange<int>(0, 10);
    for (int i = 0; i < numFilePaths; ++i) {
        params.filePaths.push_back(Path(QString::fromStdString(fuzzed_data.ConsumeRandomLengthString(512))));
    }

    // File priorities
    int numFilePriorities = fuzzed_data.ConsumeIntegralInRange<int>(0, 10);
    for (int i = 0; i < numFilePriorities; ++i) {
        params.filePriorities.push_back(static_cast<BitTorrent::DownloadPriority>(fuzzed_data.ConsumeIntegral<uint8_t>()));
    }

    // Finally, fuzz the addTorrent function
    MockApplication mockApp;
    BitTorrent::MockSession mockSession;
    TestAddTorrentManager manager(&mockApp, &mockSession);
    // manager.addTorrent(source, params);

    Net::DownloadManager::hasSupportedScheme(source);
    Net::DownloadRequest source_request(source);
    // if (const auto parseResult = BitTorrent::TorrentDescriptor::parse(source)) {
    //     manager.processTorrent(source, parseResult.value(), params);
    // } else {
    //     manager.handleAddTorrentFailed(source, parseResult.error());
    // }
    BitTorrent::TorrentDescriptor::parse(source)
}
