# IWC_DEV
#github test


## Architecture
IWC POC레벨 Dapp은 총 4개의 상위 모듈로 구성된다.

1. append
2. api_call
3. push_data
4. ui/ux

```
1. append
append 모듈은 c++로 작성된다.
append class는 다양한 스트링값을 조합+헤쉬하여 api URL을 생성한다.
append class에는 URL생성에 필요한 여러 파라미터가 하드코딩되어 있다.
내부적으로 스트링을 합치는 함수, 해쉬하는 함수, URL생성 함수가 작성된다.
```

```
2. api_call
api_call 모듈은 c++로 작성된다.
api_call class는 append class에서 아웃풋된 URL을 이용하여
api call을 한다. api 데이터를 json형식의 스트링으로 받는다.
```

```
3. push_data
push_data 모듈은 c++로 작성된다.
api_call class가 생성한 json형식의 스트링을
uploadToBlockchain함수는 push_trx.sh파일을 이용하여 ibct private net으로 push한다.
push_trx.sh 파일은 트렌젝션을 푸시하고 나오는 리턴값 중 트렌젝션 넘버 / 헤쉬를 다시 api_call class로 전달한다.
mergeData함수는 api_call class에서 아웃풋된 json스트링 값과 getTransactionNum함수와 getHash함수를 이용하여 전달받은
값을 하나의 스트링으로 합친다.
createJSON함수는 이전 단계에서 하나로 합쳐진 스트링을 가지고 json file을 생성하여 디렉토리에 저장한다. 그리고 filename을 return한다.
uploadToDB함수는 filename을 이용하여 json파일을 DB로 업로드한다.
```

```
4. ui/ux
DB에 저장된 정보를 받아서 디스플레이.
```
