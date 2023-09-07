#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h> // Inclua a biblioteca para printf
#include <vector>
#include <sndfile.h>

int main() {
    // Inicializar o dispositivo OpenAL
    ALCdevice* device = alcOpenDevice(nullptr);
    if (!device) {
        printf("Erro ao inicializar o dispositivo OpenAL\n");
        return 1;
    }

    ALCcontext* context = alcCreateContext(device, nullptr);
    alcMakeContextCurrent(context);

    // Carregar um arquivo de áudio (substitua com o caminho do seu próprio arquivo)
    const char* arquivoAudio = "shot0.wav";

    ALuint buffer;
    alGenBuffers(1, &buffer);

    ALenum formato;
    ALsizei tamanho;
    ALvoid* dados;
    ALsizei frequencia;
    ALboolean loop = AL_FALSE;

    ALuint source;
    alGenSources(1, &source);

    ALint estado;

    // Abrir o arquivo de áudio usando libsndfile
    SF_INFO sfInfo;
    SNDFILE* sndFile = sf_open(arquivoAudio, SFM_READ, &sfInfo);

    if (!sndFile) {
        printf("Erro ao abrir o arquivo de áudio\n");
        return 1;
    }

    // Ler os dados do arquivo de áudio e preencher o buffer OpenAL
    std::vector<ALshort> bufferData(sfInfo.frames * sfInfo.channels);
    sf_read_short(sndFile, &bufferData[0], bufferData.size());

    formato = (sfInfo.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    tamanho = static_cast<ALsizei>(bufferData.size() * sizeof(ALshort));
    frequencia = sfInfo.samplerate;

    // Preencher o buffer OpenAL
    alBufferData(buffer, formato, &bufferData[0], tamanho, frequencia);

    // Associar o buffer ao source
    alSourcei(source, AL_BUFFER, buffer);

    // Reproduzir o áudio
    alSourcePlay(source);

    // Esperar até que a reprodução termine
    do {
        alGetSourcei(source, AL_SOURCE_STATE, &estado);
    } while (estado == AL_PLAYING);

    // Limpar e encerrar o contexto e o dispositivo
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    sf_close(sndFile);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}
