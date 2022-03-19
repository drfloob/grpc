Search.setIndex({docnames:["glossary","grpc","grpc_admin","grpc_asyncio","grpc_channelz","grpc_csds","grpc_health_checking","grpc_reflection","grpc_status","grpc_testing","index"],envversion:{"sphinx.domains.c":2,"sphinx.domains.changeset":1,"sphinx.domains.citation":1,"sphinx.domains.cpp":4,"sphinx.domains.index":1,"sphinx.domains.javascript":2,"sphinx.domains.math":2,"sphinx.domains.python":3,"sphinx.domains.rst":2,"sphinx.domains.std":2,"sphinx.ext.todo":2,"sphinx.ext.viewcode":1,sphinx:56},filenames:["glossary.rst","grpc.rst","grpc_admin.rst","grpc_asyncio.rst","grpc_channelz.rst","grpc_csds.rst","grpc_health_checking.rst","grpc_reflection.rst","grpc_status.rst","grpc_testing.rst","index.rst"],objects:{"":[[1,0,0,"-","grpc"],[2,0,0,"-","grpc_admin"],[5,0,0,"-","grpc_csds"],[9,0,0,"-","grpc_testing"]],"grpc.AuthMetadataContext":[[1,2,1,"","method_name"],[1,2,1,"","service_url"]],"grpc.AuthMetadataPlugin":[[1,3,1,"","__call__"]],"grpc.AuthMetadataPluginCallback":[[1,3,1,"","__call__"]],"grpc.Call":[[1,3,1,"","code"],[1,3,1,"","details"],[1,3,1,"","initial_metadata"],[1,3,1,"","trailing_metadata"]],"grpc.Channel":[[1,3,1,"","__enter__"],[1,3,1,"","__exit__"],[1,3,1,"","close"],[1,3,1,"","stream_stream"],[1,3,1,"","stream_unary"],[1,3,1,"","subscribe"],[1,3,1,"","unary_stream"],[1,3,1,"","unary_unary"],[1,3,1,"","unsubscribe"]],"grpc.ChannelConnectivity":[[1,2,1,"","CONNECTING"],[1,2,1,"","IDLE"],[1,2,1,"","READY"],[1,2,1,"","SHUTDOWN"],[1,2,1,"","TRANSIENT_FAILURE"]],"grpc.ClientCallDetails":[[1,2,1,"","compression"],[1,2,1,"","credentials"],[1,2,1,"","metadata"],[1,2,1,"","method"],[1,2,1,"","timeout"],[1,2,1,"","wait_for_ready"]],"grpc.Compression":[[1,2,1,"","Deflate"],[1,2,1,"","Gzip"],[1,2,1,"","NoCompression"]],"grpc.Future":[[1,3,1,"","add_done_callback"],[1,3,1,"","cancel"],[1,3,1,"","cancelled"],[1,3,1,"","done"],[1,3,1,"","exception"],[1,3,1,"","result"],[1,3,1,"","running"],[1,3,1,"","traceback"]],"grpc.GenericRpcHandler":[[1,3,1,"","service"]],"grpc.HandlerCallDetails":[[1,2,1,"","invocation_metadata"],[1,2,1,"","method"]],"grpc.LocalConnectionType":[[1,2,1,"","LOCAL_TCP"],[1,2,1,"","UDS"]],"grpc.RpcContext":[[1,3,1,"","add_callback"],[1,3,1,"","cancel"],[1,3,1,"","is_active"],[1,3,1,"","time_remaining"]],"grpc.RpcMethodHandler":[[1,2,1,"","request_deserializer"],[1,2,1,"","request_streaming"],[1,2,1,"","response_serializer"],[1,2,1,"","response_streaming"],[1,2,1,"","stream_stream"],[1,2,1,"","stream_unary"],[1,2,1,"","unary_stream"],[1,2,1,"","unary_unary"]],"grpc.Server":[[1,3,1,"","add_generic_rpc_handlers"],[1,3,1,"","add_insecure_port"],[1,3,1,"","add_secure_port"],[1,3,1,"","start"],[1,3,1,"","stop"],[1,3,1,"","wait_for_termination"]],"grpc.ServerInterceptor":[[1,3,1,"","intercept_service"]],"grpc.ServiceRpcHandler":[[1,3,1,"","service_name"]],"grpc.ServicerContext":[[1,3,1,"","abort"],[1,3,1,"","abort_with_status"],[1,3,1,"","auth_context"],[1,3,1,"","code"],[1,3,1,"","details"],[1,3,1,"","disable_next_message_compression"],[1,3,1,"","invocation_metadata"],[1,3,1,"","peer"],[1,3,1,"","peer_identities"],[1,3,1,"","peer_identity_key"],[1,3,1,"","send_initial_metadata"],[1,3,1,"","set_code"],[1,3,1,"","set_compression"],[1,3,1,"","set_details"],[1,3,1,"","set_trailing_metadata"],[1,3,1,"","trailing_metadata"]],"grpc.StatusCode":[[1,2,1,"","ABORTED"],[1,2,1,"","ALREADY_EXISTS"],[1,2,1,"","CANCELLED"],[1,2,1,"","DATA_LOSS"],[1,2,1,"","DEADLINE_EXCEEDED"],[1,2,1,"","FAILED_PRECONDITION"],[1,2,1,"","INTERNAL"],[1,2,1,"","INVALID_ARGUMENT"],[1,2,1,"","NOT_FOUND"],[1,2,1,"","OK"],[1,2,1,"","PERMISSION_DENIED"],[1,2,1,"","RESOURCE_EXHAUSTED"],[1,2,1,"","UNAUTHENTICATED"],[1,2,1,"","UNAVAILABLE"],[1,2,1,"","UNIMPLEMENTED"],[1,2,1,"","UNKNOWN"]],"grpc.StreamStreamClientInterceptor":[[1,3,1,"","intercept_stream_stream"]],"grpc.StreamStreamMultiCallable":[[1,3,1,"","__call__"]],"grpc.StreamUnaryClientInterceptor":[[1,3,1,"","intercept_stream_unary"]],"grpc.StreamUnaryMultiCallable":[[1,3,1,"","__call__"],[1,3,1,"","future"],[1,3,1,"","with_call"]],"grpc.UnaryStreamClientInterceptor":[[1,3,1,"","intercept_unary_stream"]],"grpc.UnaryStreamMultiCallable":[[1,3,1,"","__call__"]],"grpc.UnaryUnaryClientInterceptor":[[1,3,1,"","intercept_unary_unary"]],"grpc.UnaryUnaryMultiCallable":[[1,3,1,"","__call__"],[1,3,1,"","future"],[1,3,1,"","with_call"]],"grpc.aio":[[3,4,1,"","AbortError"],[3,4,1,"","AioRpcError"],[3,4,1,"","BaseError"],[3,1,1,"","Call"],[3,1,1,"","Channel"],[3,1,1,"","ClientCallDetails"],[3,1,1,"","ClientInterceptor"],[3,1,1,"","InterceptedUnaryUnaryCall"],[3,4,1,"","InternalError"],[3,1,1,"","Metadata"],[3,1,1,"","RpcContext"],[3,1,1,"","Server"],[3,1,1,"","ServerInterceptor"],[3,1,1,"","ServicerContext"],[3,1,1,"","StreamStreamCall"],[3,1,1,"","StreamStreamClientInterceptor"],[3,1,1,"","StreamStreamMultiCallable"],[3,1,1,"","StreamUnaryCall"],[3,1,1,"","StreamUnaryClientInterceptor"],[3,1,1,"","StreamUnaryMultiCallable"],[3,1,1,"","UnaryStreamCall"],[3,1,1,"","UnaryStreamClientInterceptor"],[3,1,1,"","UnaryStreamMultiCallable"],[3,1,1,"","UnaryUnaryCall"],[3,1,1,"","UnaryUnaryClientInterceptor"],[3,1,1,"","UnaryUnaryMultiCallable"],[3,4,1,"","UsageError"],[3,5,1,"","insecure_channel"],[3,5,1,"","secure_channel"],[3,5,1,"","server"]],"grpc.aio.AioRpcError":[[3,3,1,"","code"],[3,3,1,"","debug_error_string"],[3,3,1,"","details"],[3,3,1,"","initial_metadata"],[3,3,1,"","trailing_metadata"]],"grpc.aio.Call":[[3,3,1,"","code"],[3,3,1,"","details"],[3,3,1,"","initial_metadata"],[3,3,1,"","trailing_metadata"],[3,3,1,"","wait_for_connection"]],"grpc.aio.Channel":[[3,3,1,"","__aenter__"],[3,3,1,"","__aexit__"],[3,3,1,"","channel_ready"],[3,3,1,"","close"],[3,3,1,"","get_state"],[3,3,1,"","stream_stream"],[3,3,1,"","stream_unary"],[3,3,1,"","unary_stream"],[3,3,1,"","unary_unary"],[3,3,1,"","wait_for_state_change"]],"grpc.aio.InterceptedUnaryUnaryCall":[[3,3,1,"","time_remaining"]],"grpc.aio.Metadata":[[3,3,1,"","__delitem__"],[3,3,1,"","__getitem__"],[3,3,1,"","__len__"],[3,3,1,"","__setitem__"],[3,3,1,"","delete_all"],[3,3,1,"","get_all"]],"grpc.aio.RpcContext":[[3,3,1,"","add_done_callback"],[3,3,1,"","cancel"],[3,3,1,"","cancelled"],[3,3,1,"","done"],[3,3,1,"","time_remaining"]],"grpc.aio.Server":[[3,3,1,"","add_generic_rpc_handlers"],[3,3,1,"","add_insecure_port"],[3,3,1,"","add_secure_port"],[3,3,1,"","start"],[3,3,1,"","stop"],[3,3,1,"","wait_for_termination"]],"grpc.aio.ServerInterceptor":[[3,3,1,"","intercept_service"]],"grpc.aio.ServicerContext":[[3,3,1,"","abort"],[3,3,1,"","add_done_callback"],[3,3,1,"","auth_context"],[3,3,1,"","cancelled"],[3,3,1,"","code"],[3,3,1,"","details"],[3,3,1,"","disable_next_message_compression"],[3,3,1,"","done"],[3,3,1,"","invocation_metadata"],[3,3,1,"","peer"],[3,3,1,"","peer_identities"],[3,3,1,"","peer_identity_key"],[3,3,1,"","read"],[3,3,1,"","send_initial_metadata"],[3,3,1,"","set_code"],[3,3,1,"","set_compression"],[3,3,1,"","set_details"],[3,3,1,"","set_trailing_metadata"],[3,3,1,"","time_remaining"],[3,3,1,"","trailing_metadata"],[3,3,1,"","write"]],"grpc.aio.StreamStreamCall":[[3,3,1,"","__aiter__"],[3,3,1,"","done_writing"],[3,3,1,"","read"],[3,3,1,"","write"]],"grpc.aio.StreamStreamClientInterceptor":[[3,3,1,"","intercept_stream_stream"]],"grpc.aio.StreamStreamMultiCallable":[[3,3,1,"","__call__"]],"grpc.aio.StreamUnaryCall":[[3,3,1,"","__await__"],[3,3,1,"","done_writing"],[3,3,1,"","write"]],"grpc.aio.StreamUnaryClientInterceptor":[[3,3,1,"","intercept_stream_unary"]],"grpc.aio.StreamUnaryMultiCallable":[[3,3,1,"","__call__"]],"grpc.aio.UnaryStreamCall":[[3,3,1,"","__aiter__"],[3,3,1,"","read"]],"grpc.aio.UnaryStreamClientInterceptor":[[3,3,1,"","intercept_unary_stream"]],"grpc.aio.UnaryStreamMultiCallable":[[3,3,1,"","__call__"]],"grpc.aio.UnaryUnaryCall":[[3,3,1,"","__await__"]],"grpc.aio.UnaryUnaryClientInterceptor":[[3,3,1,"","intercept_unary_unary"]],"grpc.aio.UnaryUnaryMultiCallable":[[3,3,1,"","__call__"]],"grpc_channelz.v1":[[4,0,0,"-","channelz"]],"grpc_channelz.v1.channelz":[[4,1,1,"","ChannelzServicer"],[4,5,1,"","add_channelz_servicer"]],"grpc_channelz.v1.channelz.ChannelzServicer":[[4,3,1,"","GetChannel"],[4,3,1,"","GetServer"],[4,3,1,"","GetServerSockets"],[4,3,1,"","GetServers"],[4,3,1,"","GetSocket"],[4,3,1,"","GetSubchannel"],[4,3,1,"","GetTopChannels"]],"grpc_csds.ClientStatusDiscoveryServiceServicer":[[5,3,1,"","FetchClientStatus"],[5,3,1,"","StreamClientStatus"]],"grpc_health.v1.health":[[6,1,1,"","HealthServicer"]],"grpc_health.v1.health.HealthServicer":[[6,3,1,"","Check"],[6,3,1,"","Watch"],[6,3,1,"","enter_graceful_shutdown"],[6,3,1,"","set"]],"grpc_reflection.v1alpha":[[7,0,0,"-","reflection"]],"grpc_reflection.v1alpha.reflection":[[7,1,1,"","ReflectionServicer"],[7,5,1,"","enable_server_reflection"]],"grpc_reflection.v1alpha.reflection.ReflectionServicer":[[7,3,1,"","ServerReflectionInfo"]],"grpc_status.rpc_status":[[8,5,1,"","from_call"],[8,5,1,"","to_status"]],"grpc_testing.Channel":[[9,3,1,"","take_stream_stream"],[9,3,1,"","take_stream_unary"],[9,3,1,"","take_unary_stream"],[9,3,1,"","take_unary_unary"]],"grpc_testing.Server":[[9,3,1,"","invoke_stream_stream"],[9,3,1,"","invoke_stream_unary"],[9,3,1,"","invoke_unary_stream"],[9,3,1,"","invoke_unary_unary"]],"grpc_testing.StreamStreamChannelRpc":[[9,3,1,"","cancelled"],[9,3,1,"","requests_closed"],[9,3,1,"","send_initial_metadata"],[9,3,1,"","send_response"],[9,3,1,"","take_request"],[9,3,1,"","terminate"]],"grpc_testing.StreamStreamServerRpc":[[9,3,1,"","cancel"],[9,3,1,"","initial_metadata"],[9,3,1,"","requests_closed"],[9,3,1,"","send_request"],[9,3,1,"","take_response"],[9,3,1,"","termination"]],"grpc_testing.StreamUnaryChannelRpc":[[9,3,1,"","cancelled"],[9,3,1,"","requests_closed"],[9,3,1,"","send_initial_metadata"],[9,3,1,"","take_request"],[9,3,1,"","terminate"]],"grpc_testing.StreamUnaryServerRpc":[[9,3,1,"","cancel"],[9,3,1,"","initial_metadata"],[9,3,1,"","requests_closed"],[9,3,1,"","send_request"],[9,3,1,"","termination"]],"grpc_testing.Time":[[9,3,1,"","call_at"],[9,3,1,"","call_in"],[9,3,1,"","sleep_for"],[9,3,1,"","sleep_until"],[9,3,1,"","time"]],"grpc_testing.UnaryStreamChannelRpc":[[9,3,1,"","cancelled"],[9,3,1,"","send_initial_metadata"],[9,3,1,"","send_response"],[9,3,1,"","terminate"]],"grpc_testing.UnaryStreamServerRpc":[[9,3,1,"","cancel"],[9,3,1,"","initial_metadata"],[9,3,1,"","take_response"],[9,3,1,"","termination"]],"grpc_testing.UnaryUnaryChannelRpc":[[9,3,1,"","cancelled"],[9,3,1,"","send_initial_metadata"],[9,3,1,"","terminate"]],"grpc_testing.UnaryUnaryServerRpc":[[9,3,1,"","cancel"],[9,3,1,"","initial_metadata"],[9,3,1,"","termination"]],grpc:[[1,1,1,"","AuthMetadataContext"],[1,1,1,"","AuthMetadataPlugin"],[1,1,1,"","AuthMetadataPluginCallback"],[1,1,1,"","Call"],[1,1,1,"","CallCredentials"],[1,1,1,"","Channel"],[1,1,1,"","ChannelConnectivity"],[1,1,1,"","ChannelCredentials"],[1,1,1,"","ClientCallDetails"],[1,1,1,"","Compression"],[1,1,1,"","Future"],[1,4,1,"","FutureCancelledError"],[1,4,1,"","FutureTimeoutError"],[1,1,1,"","GenericRpcHandler"],[1,1,1,"","HandlerCallDetails"],[1,1,1,"","LocalConnectionType"],[1,1,1,"","RpcContext"],[1,4,1,"","RpcError"],[1,1,1,"","RpcMethodHandler"],[1,1,1,"","Server"],[1,1,1,"","ServerCertificateConfiguration"],[1,1,1,"","ServerCredentials"],[1,1,1,"","ServerInterceptor"],[1,1,1,"","ServiceRpcHandler"],[1,1,1,"","ServicerContext"],[1,1,1,"","StatusCode"],[1,1,1,"","StreamStreamClientInterceptor"],[1,1,1,"","StreamStreamMultiCallable"],[1,1,1,"","StreamUnaryClientInterceptor"],[1,1,1,"","StreamUnaryMultiCallable"],[1,1,1,"","UnaryStreamClientInterceptor"],[1,1,1,"","UnaryStreamMultiCallable"],[1,1,1,"","UnaryUnaryClientInterceptor"],[1,1,1,"","UnaryUnaryMultiCallable"],[1,5,1,"","access_token_call_credentials"],[3,0,0,"-","aio"],[1,5,1,"","channel_ready_future"],[1,5,1,"","composite_call_credentials"],[1,5,1,"","composite_channel_credentials"],[1,5,1,"","compute_engine_channel_credentials"],[1,5,1,"","dynamic_ssl_server_credentials"],[1,5,1,"","insecure_channel"],[1,5,1,"","intercept_channel"],[1,5,1,"","local_channel_credentials"],[1,5,1,"","local_server_credentials"],[1,5,1,"","metadata_call_credentials"],[1,5,1,"","method_handlers_generic_handler"],[1,5,1,"","protos"],[1,5,1,"","protos_and_services"],[1,5,1,"","secure_channel"],[1,5,1,"","server"],[1,5,1,"","services"],[1,5,1,"","ssl_channel_credentials"],[1,5,1,"","ssl_server_certificate_configuration"],[1,5,1,"","ssl_server_credentials"],[1,5,1,"","stream_stream_rpc_method_handler"],[1,5,1,"","stream_unary_rpc_method_handler"],[1,5,1,"","unary_stream_rpc_method_handler"],[1,5,1,"","unary_unary_rpc_method_handler"]],grpc_admin:[[2,5,1,"","add_admin_servicers"]],grpc_csds:[[5,1,1,"","ClientStatusDiscoveryServiceServicer"],[5,5,1,"","add_csds_servicer"]],grpc_status:[[8,0,0,"-","rpc_status"]],grpc_testing:[[9,1,1,"","Channel"],[9,1,1,"","Server"],[9,1,1,"","StreamStreamChannelRpc"],[9,1,1,"","StreamStreamServerRpc"],[9,1,1,"","StreamUnaryChannelRpc"],[9,1,1,"","StreamUnaryServerRpc"],[9,1,1,"","Time"],[9,1,1,"","UnaryStreamChannelRpc"],[9,1,1,"","UnaryStreamServerRpc"],[9,1,1,"","UnaryUnaryChannelRpc"],[9,1,1,"","UnaryUnaryServerRpc"],[9,5,1,"","channel"],[9,5,1,"","server_from_dictionary"],[9,5,1,"","strict_fake_time"],[9,5,1,"","strict_real_time"]]},objnames:{"0":["py","module","Python module"],"1":["py","class","Python class"],"2":["py","attribute","Python attribute"],"3":["py","method","Python method"],"4":["py","exception","Python exception"],"5":["py","function","Python function"]},objtypes:{"0":"py:module","1":"py:class","2":"py:attribute","3":"py:method","4":"py:exception","5":"py:function"},terms:{"0":[0,1,3,4,10],"1":[1,4,10],"10000":1,"2":[0,1],"3":[1,3],"45":[0,1,2,3,4,5,6,7,8,9,10],"8":[1,3],"abstract":[1,3,9],"boolean":1,"byte":[0,1,3],"case":[1,3],"catch":3,"class":[1,3,4,5,6,7,9],"default":[0,1,4,7],"do":1,"enum":6,"final":[1,3],"float":[1,3],"function":[0,1,3],"import":2,"int":3,"long":9,"new":[1,2,3,6],"return":[0,1,3,4,8,9],"short":5,"static":[4,5],"true":[1,3,6],"try":3,"while":1,A:[0,1,2,3,4,5,8,9],At:1,By:0,For:[0,1,3],IS:1,If:[0,1,3,6,8,9],In:[1,5],It:[0,1,2,3,4,5,6],Not:1,On:0,One:1,That:4,The:[0,1,3,4,6,7,9],There:3,To:[1,3],With:2,__aenter__:3,__aexit__:3,__aiter__:3,__await__:3,__call__:[1,3],__delitem__:3,__enter__:1,__exit__:1,__getitem__:3,__len__:3,__setitem__:3,__version__:1,_base:3,_base_cal:3,_base_channel:3,_call:3,_cython:3,_eof:3,_interceptor:3,_metadata:3,_pb2:1,_pb2_grpc:[1,9],_type:3,abort:[1,3],abort_with_statu:1,aborterror:3,about:1,accept:[1,3],access:[1,3,9],access_token:1,access_token_call_credenti:1,account:1,action:[1,3],activ:[1,3],actual:[1,3],ad:[1,2,3,4,5,7,9],add:[1,2,3,4,9],add_admin_servic:2,add_callback:1,add_channelz_servic:4,add_csds_servic:5,add_done_callback:[1,3],add_generic_rpc_handl:[1,3],add_insecure_port:[1,3],add_secure_port:[1,3],addit:3,address:[1,3],admin:10,advanc:[0,9],affect:1,afford:[1,3],after:[1,3,6,9],again:1,aio:3,aiorpcerror:3,aka:3,algorithm:[1,3],all:[1,2,3,4,6,7,9],allot:1,allow:[0,1,3,4],alreadi:[1,3],already_exist:1,also:[1,3],alt:1,although:[1,3],alwai:[1,3],an:[0,1,3,4,6,8,9],ani:[0,1,2,3,6,9],anoth:1,api:[0,1,2,4,5,6,8],applic:[0,1,3,4,9],appropri:6,ar:[0,1,2,3,8],arbitrari:[1,3],arbitrarili:1,architectur:3,arg:3,argument:[0,1,3,9],arriv:1,ascii:0,assert:1,associ:5,assum:6,async:3,asynchron:[1,3],asyncio:[5,10],asynciter:3,asyncrhon:3,attempt:[1,6],auth:[1,3],auth_context:[1,3],authent:[3,10],authmetadatacontext:1,authmetadataplugin:1,authmetadataplugincallback:1,author:[9,10],automat:2,avail:[0,1,2,7],await:3,b:0,back:[6,9],backend:5,backoff:6,balanc:3,base:3,baseerror:3,bearer:1,becam:1,becaus:1,becom:[3,6],been:[0,1,3,9],befor:[0,1,3,9],begin:1,begun:1,behavior:[1,5,9],behind:1,being:[0,1,3,9],belong:1,best:3,better:1,between:3,beyond:9,bidirect:[3,7],bin:0,binari:0,blob:[0,1,2,3,4,5,6,7,8,9,10],block:[1,9,10],bool:[1,3],both:[0,1,5],broken:1,bug:3,build:3,busi:1,c:[3,4],call:[1,3,6,8,9],call_at:9,call_credenti:1,call_in:9,callabl:[0,10],callback:[1,3,9],callcredenti:[1,3],caller:[1,3],can:[0,1,2,3,4,9],cancel:[1,3,9],cancellederror:3,cannot:[0,1],carefulli:3,caus:9,caveat:10,certain:3,certif:1,certificate_chain:1,certificate_configur:1,certificate_configuration_fetch:1,chain:[1,3],chang:[1,3,6,9],channel:[0,4,9,10],channel_argu:[0,1,3],channel_credenti:1,channel_readi:3,channel_ready_futur:1,channelconnect:[1,3],channelcredenti:[1,3],channelz:[5,10],channelzservic:4,charg:4,check:[1,3,7,10],choos:[1,3],chosen:1,circumst:1,clean:3,client:[0,6,8,9,10],client_call_detail:[1,3],clientcalldetail:[1,3],clientinterceptor:3,clientstatusdiscoveryserviceservic:5,close:[1,3,9],cloud:1,code:[4,8,9,10],codegen:[0,1,2,3,4,5,6,7,8,9,10],collect:1,com:[0,1,2,3,4,5,6,7,8,9,10],comment:5,commun:[3,8],compat:3,complet:[1,3],compos:1,composit:1,composite_call_credenti:1,composite_channel_credenti:1,compress:[3,10],comput:[1,3],compute_engine_channel_credenti:1,concurr:[1,3],condit:[1,3],conduct:1,confidenti:1,config:1,configur:[0,1,3,5],conjunct:1,connect:[0,3,9,10],consid:[1,3],construct:[0,1],consum:[1,2,3],contain:0,context:[4,5,6,7,10],continu:[1,3],control:[1,3,5],conveni:2,converg:3,convert:8,core:[0,1,3,4],coroutin:3,correspond:[1,8],corrupt:1,could:[1,3,5],creat:[2,4,9,10],creation:[1,3],credenti:[3,10],csd:10,current:[1,3,6,9],custom:[0,1],cygrpc:3,data:[1,3,5],data_loss:1,date:3,deadlin:[0,1,3],deadline_exceed:1,debug:[1,2,3,4,5],debug_error_str:3,decid:[1,3],decod:0,decoupl:1,defin:[1,9],definit:1,deflat:1,del:3,delai:9,delet:3,delete_al:3,depend:[1,2],deriv:1,describ:[1,3,9],descript:3,descriptor:9,descriptor_pool:7,descriptorpool:7,descriptors_to_servic:9,deseri:[0,1,3],design:[2,3,4,5],desir:3,detail:[1,3,8,9],determin:[1,3],dictionari:[1,9],did:1,differ:3,dir:1,directli:[1,4],directori:1,disabl:[0,1,3,4],disable_next_message_compress:[1,3],doc:[1,3],document:[0,1,2,3,4,5],doe:[1,4,9],doesn:[0,3],domain:1,done:[1,3],done_writ:3,doubl:9,down:0,draw:[1,9],due:[1,5],dump:5,durat:[1,3,9],dure:[1,3],dynamic_ssl_server_credenti:1,e:[0,1,3,4],each:[1,2,3],easier:2,effect:[1,3,5],either:[0,1,9],element:[1,3],elimin:1,els:4,emit:9,enabl:[1,3,4,7,9],enable_channelz:4,enable_server_reflect:7,encapsul:[1,3],encod:[0,1,3],encrypt:1,end:[0,1,3,9],endpoint:[1,3],engin:1,ensur:[3,7,9],enter:[1,3,6],enter_graceful_shutdown:6,entir:[1,3,4],entiti:1,entri:[0,1,3],enumer:1,environ:1,eof:3,equival:[1,3],error:[1,3],etc:[1,3],even:[0,3],event:[1,3],eventu:3,everi:[1,3],exactli:1,exampl:[0,1,3,10],exc_tb:[1,3],exc_typ:[1,3],exc_val:[1,3],except:10,execut:[1,3,9],executor:3,exhaust:1,exist:[1,2,3,4],exit:[1,3],expect:[1,3],experiment:[0,1,3,4,6,8],experimental_non_block:6,experimental_thread_pool:6,expir:1,explain:3,exponenti:6,expos:[2,5],extens:3,fail:[0,1,3,6],failed_precondit:1,failur:[1,3],fals:[1,3],fast:0,feel:3,fetch:1,fetchclientstatu:5,file:[0,1,5],filesystem:1,finish:[1,3],finsh:3,first:[0,3],fixtur:9,flag:[1,3],flow:[1,3],fn:1,focus:5,follow:[1,3],foo:1,form:1,format:[1,3],forward:[1,3],found:[0,1,3],free:3,from:[1,3,4,9],from_cal:8,fulfil:1,full:0,fulli:[1,7],further:3,futur:[2,3,6,9,10],futurecancellederror:1,futuretimeouterror:1,g:[0,1,3],gain:1,gcp:1,gener:[1,3,9],generic_rpc_handl:[1,3],genericrpchandl:[1,3],get:[1,2,3,4],get_al:3,get_stat:3,getchannel:4,getserv:4,getserversocket:4,getsocket:4,getsubchannel:4,gettopchannel:4,github:[0,1,2,3,4,5,6,7,8,9,10],given:[1,3,8,9],glossari:10,go:7,goe:[1,3],googl:[1,8],grace:[1,3,6],grfc:3,grpc:0,grpc_admin:2,grpc_arg_kei:0,grpc_channelz:4,grpc_connectivity_st:1,grpc_csd:5,grpc_health:6,grpc_python_disable_dynamic_stub:1,grpc_reflect:7,grpc_statu:8,grpc_status_cod:1,grpc_test:9,grpc_type:[0,1,2,3,4,5,6,7,8,9,10],guarante:3,gzip:[1,3],h:[0,1,2,3,4,5,6,7,8,9,10],ha:[0,1,3,4,9],hand:[1,3],handl:[1,4,6,7],handler:[0,3,10],handler_call_detail:[1,3],handlercalldetail:[1,3],handshak:1,happen:3,have:[0,1,3,9],haven:3,header:[0,1],health:10,healthcheckrespons:6,healthservic:6,held:[1,3],henc:3,here:3,hood:3,html:[1,3],http:[0,1,2,3,4,5,6,7,8,9,10],i:[0,1,3,4],idempot:[1,3],ident:[1,3],identifi:[1,3,9],idl:[0,1],ignor:6,immedi:[0,1,3,6],immut:3,impl:[0,1,2,3,4,5,6,7,8,9,10],implement:[1,3,4,5,7,8,9],imposs:1,improv:2,inappropri:3,inbound:0,includ:[0,1,2,3,4,5,6,7,8,9,10],incom:[1,3],inconsist:8,independ:9,index:10,indic:[1,3,6,9],infinit:1,info:[1,4],inform:[1,3,4],inher:3,initi:[1,2,3,9],initial_certificate_configur:1,initial_metadata:[1,3,9],input:[0,8],insecur:[1,3],insecure_channel:[1,3],insid:[4,8],inspect:1,instanc:[1,3,8,9],instanti:3,integ:[1,3],intercept:[1,3],intercept_channel:1,intercept_servic:[1,3],intercept_stream_stream:[1,3],intercept_stream_unari:[1,3],intercept_unary_stream:[1,3],intercept_unary_unari:[1,3],interceptedunaryunarycal:3,interceptor:10,interfac:[2,9,10],intern:[1,2,9],internalerror:3,interpret:9,invalid:1,invalid_argu:1,invari:1,invoc:[1,3,9],invocation_metadata:[1,3,9],invok:[0,1,3,6,9],invoke_stream_stream:9,invoke_stream_unari:9,invoke_unary_stream:9,invoke_unary_unari:9,io:[1,3],is_act:[1,9],isn:0,isol:4,issu:[0,1,3,5],item:3,iter:[1,3,7,9],its:[1,3,9],java:3,just:[1,2],kei:[0,1,3],known:[0,3,6],kwd:3,label:0,languag:3,larger:[1,3],last:[1,3],last_observed_st:3,later:[1,3],layer:1,least:1,length:[1,3,9],level:[1,4],librari:[0,1,2,3],lifetim:[1,3],like:[0,1,3],limit:[1,3,9],list:[0,1,3],live:9,load:3,local:[3,10],local_channel_credenti:1,local_connect_typ:1,local_server_credenti:1,local_tcp:1,localconnectiontyp:1,localhost:1,locat:1,log:1,logic:[1,3],longer:3,lookup:[1,3],loop:3,loss:1,machin:1,machineri:1,made:9,mai:[0,1,2,3,9],maintain:9,make:[1,2,3],manag:[1,2,3],mani:[1,3],manipul:[1,3,9],map:[1,3,8],matur:1,maximum:[1,3],maximum_concurrent_rpc:[1,3],mean:[1,4],meant:0,mechan:[1,3],mere:1,messag:[0,1,3,6,8,9],met:[1,3],metadata:[0,1,9,10],metadata_call_credenti:1,metadata_plugin:1,metadatum:0,method:[3,6,9,10],method_descriptor:9,method_handl:1,method_handlers_generic_handl:1,method_nam:1,methoddescriptor:9,migrat:3,migration_thread_pool:3,mirror:1,misconfigur:5,miss:5,mix:3,modul:10,moment:0,monitor:1,more:[1,3,9],most:[1,3],move:[1,3],multi:10,multipl:[1,3],must:[0,1,3],mutat:3,name:[0,1,3,6,7],nativ:3,need:[1,3],needn:9,network:3,next:[1,3],nocompress:1,non:[1,3,4,8],none:[0,1,3,6,7,9],nonneg:[1,3],nor:4,not_found:[1,4,6],not_serv:6,notifi:3,now:9,number:[1,3],object:[0,7,9,10],observ:[1,3],occur:[1,3],ok:[1,3,6,8],omit:1,onc:[1,3],one:[1,2,3,9],ones:[1,3],ongo:1,onli:[1,3,9],open:[1,3],oper:[1,3],opposit:1,option:[0,1,3,4],order:[1,3,9],org:[1,3],other:[0,1,3,6],otherwis:[1,3],our:3,out:[1,3,7],outbound:0,outcom:1,outgo:[1,3],over:[1,3,9],overrid:[1,3],overridden:[1,3],overview:10,packag:2,page:[1,10],pair:[0,1,3],paramet:[1,2,3,4,5,6,7,8,9],pars:10,part:[1,5],partial:3,pass:[1,3],passag:9,path:1,peer:[1,3],peer_ident:[1,3],peer_identity_kei:[1,3],pem:1,per:1,perform:[3,6],perhap:1,period:[1,3,6],perman:6,permiss:1,permission_deni:1,place:1,plai:9,plane:5,pleas:3,plugin:1,point:[1,3,6],pool:7,port:[0,1,3],potenti:3,predefin:2,preserv:3,previous:1,print:1,privat:1,private_kei:1,private_key_certificate_chain_pair:1,proce:[1,3],process:[3,4],produc:[1,3],properti:[1,3],proto:[1,5],protobuf:[3,10],protobuf_path:1,protoc:1,protocol:[3,5],protos_and_servic:1,provid:[0,1,2,3,9],proxi:3,pull:4,purpos:3,put:3,py:1,python:[1,2,3,4,5,7,8,9],qualifi:[1,7],queri:[4,9],queue:0,quota:1,race:3,rais:[1,3,8],raw:[1,3],re:3,reach:[0,3],read:3,readi:[0,3,10],real:9,reason:[0,1,3],receiv:[1,3,6],recommend:3,recov:1,recreat:3,refer:[3,7,8],reflect:10,reflectionservic:7,regist:[1,2,3,5,9],reject:1,rel:1,relat:[1,3,7],releas:[1,3,10],reli:1,remain:[1,3],remot:3,replac:[1,3],repo:3,repres:[1,3,8],represent:[1,3,9],request:[1,3,4,5,6,7,9],request_deseri:1,request_iter:[1,3,5,7],request_seri:[1,3],request_stream:1,requests_clos:9,requesttyp:3,requir:1,require_client_auth:1,require_client_authent:1,resolut:3,resolv:1,resourc:[1,3,5],resource_exhaust:[1,3],respect:9,respons:[1,3,4,9],response_deseri:[1,3],response_futur:1,response_iter:1,response_seri:1,response_stream:1,responsetyp:3,restrict:[0,1,3],result:[0,1],retri:[3,6],retriev:[1,3],reus:0,right:2,root:[1,4],root_certif:1,rout:5,rpc:[0,3,4,6,7,8,9,10],rpc_statu:8,rpccontext:[1,3,9],rpcerror:[1,3],rpcmethodhandl:[1,3],run:[1,3],runtim:[3,10],s:[0,1,2,3,5,6,8,9],safe:[1,3],safeti:3,same:[0,1,3,9],scatter:2,schedul:1,scope:1,scratch:3,search:10,second:[0,1,3,9],secret:1,section:0,secur:[1,3],secure_channel:[1,3],see:1,seen:1,send:[1,3,6,9],send_initial_metadata:[1,3,9],send_request:9,send_respons:9,send_response_callback:6,sent:[1,3,9],separ:[1,2],sequenc:[0,1,3,9],serial:[0,1,3],serv:[3,6],server:[0,2,4,5,6,7,9,10],server_credenti:[1,3],server_from_dictionari:9,servercertificateconfigur:1,servercredenti:[1,3],serverinterceptor:[1,3],serverreflectioninfo:7,servic:[2,3,4,5,6,7,9,10],service_descriptor:9,service_nam:[1,7],service_unknown:6,service_url:1,servicedescriptor:9,servicer_context:[1,3],servicercontext:[1,3],servicerpchandl:1,set:[1,3,4,6],set_cod:[1,3],set_compress:[1,3],set_detail:[1,3],set_trailing_metadata:[1,3],setup:1,share:10,should:[1,3,6],shut:0,shutdown:[0,1,6],side:[0,10],signal:[1,3],simplifi:5,simul:9,simultan:3,sinc:3,singl:[1,4,7],sleep_for:9,sleep_until:9,smaller:[1,3],snapshot:3,so:[0,1,3],so_reuseport:0,socket:[1,4],some:[0,1,2,6,9],sooner:[1,3],sort:1,sourc:[1,2,3,4,5,6,7,8,9],space:1,specif:[1,9],specifi:[0,1,3],ssl:[1,3],ssl_channel_credenti:1,ssl_server_certificate_configur:1,ssl_server_credenti:1,stabl:3,stack:3,start:[1,3],starv:3,state:[0,1,2,3],statist:4,statu:[3,6,9,10],status:[4,6,7],statuscod:[1,3],still:[0,3],stop:[1,3],str:[0,3],stream:[1,3,7,9],stream_stream:[1,3],stream_stream_channel_rpc:9,stream_stream_rpc_method_handl:1,stream_unari:[1,3],stream_unary_channel_rpc:9,stream_unary_rpc_method_handl:1,streamclientstatu:5,streamstreamcal:3,streamstreamchannelrpc:9,streamstreamclientinterceptor:[1,3],streamstreammultical:[1,3],streamstreamserverrpc:9,streamunarycal:3,streamunarychannelrpc:9,streamunaryclientinterceptor:[1,3],streamunarymultical:[1,3],streamunaryserverrpc:9,strict:9,strict_fake_tim:9,strict_real_tim:9,string:[1,3,6],structur:[1,7],stub:[1,3],style:3,subchannel:4,submit:[0,9],subscrib:1,subscript:1,subsequ:[1,3,6],success:[1,9],successfulli:[1,3],suddenli:1,suggest:3,suitabl:1,superced:[1,3],suppli:1,support:[1,3,6],suppress:3,sy:1,sync:5,synchron:1,synthes:9,system:[1,9],t:[0,3,9],tailor:3,take:[1,3],take_request:9,take_respons:9,take_stream_stream:9,take_stream_unari:9,take_unary_stream:9,take_unary_unari:9,taken:1,target:[1,3],task:3,tcp:[0,1,3],termin:[1,3,6,8,9],test:[1,10],thei:[1,3],them:[1,2,3,9],thi:[0,1,2,3,4,6,7,8,9],those:[3,9],though:1,thread:[1,3],thread_pool:1,threadpoolexecutor:[1,3],through:1,throughout:1,thu:1,time:[1,2,3,9],time_remain:[1,3,9],timeout:[1,3,9],tl:1,to_statu:8,token:1,top:4,total:3,traceback:1,track:1,traffic:5,trail:[1,3,9],trailing_metadata:[1,3,9],trait:3,transact:1,transient_failur:[0,1],transit:[1,3],transmit:[0,1,3],transport:1,try_to_connect:[1,3],tupl:[0,1,3,9],two:[1,3],type:[3,10],typeerror:1,typic:1,ud:1,udp:3,unari:[1,3,9],unary_stream:[1,3],unary_stream_channel_rpc:9,unary_stream_rpc_method_handl:1,unary_unari:[1,3],unary_unary_channel_rpc:9,unary_unary_rpc_method_handl:1,unarysterammultical:3,unarystreamcal:3,unarystreamchannelrpc:9,unarystreamclientinterceptor:[1,3],unarystreammultical:[1,3],unarystreamserverrpc:9,unaryunarycal:3,unaryunarychannelrpc:9,unaryunaryclientinterceptor:[1,3],unaryunarymultical:[1,3],unaryunaryserverrpc:9,unauthent:1,unavail:1,under:[0,1,3,9],underli:[0,1,3],undeseri:[1,3],unexpect:[3,5],unexpectedli:1,unhealthi:5,unimpl:[1,6],union:3,unit:1,unix:1,unknown:[1,6],unless:[1,3],unrecover:1,unseri:[1,3],unsubscrib:1,until:[0,1,3,9],untouch:3,unused_context:5,up:[1,3],upgrad:2,upon:[1,3],url:1,us:[1,3,5,7,9],usabl:2,usag:[0,1,3],usageerror:3,user:[1,9],usual:[2,9],utf:[1,3],util:[1,3],v1:[0,1,2,3,4,5,6,7,8,9,10],v1alpha:7,valid:[0,1,3],valu:[0,1,3,6],valueerror:8,variabl:1,verifi:1,version:[2,3,10],via:[1,2],view:3,visibl:1,vm:1,wa:[1,3],wai:[1,2,3],wait:[1,3],wait_for:3,wait_for_connect:3,wait_for_readi:[0,1,3],wait_for_state_chang:3,wait_for_termin:[1,3],want:0,watch:6,we:[1,3],were:3,what:[1,3,10],when:[0,1,3,6,9],whenev:6,where:[0,1,3],whether:[1,3,4],which:[1,2,3,4,5,7,9],whose:3,wire:1,wish:[1,3],with_cal:1,within:[1,3],without:[1,3],work:[1,3,5],would:3,wrap:3,write:3,x00:0,x509_common_nam:[1,3],x509_subject_alternative_nam:[1,3],x:[0,1,2,3,4,5,6,7,8,9,10],xd:[1,5],xff:0,yet:1,yield:[1,3],you:[0,2,3,4],your:2,zero:1},titles:["Glossary","gRPC","gRPC Admin","gRPC AsyncIO API","gRPC Channelz","gRPC CSDS","gRPC Health Checking","gRPC Reflection","gRPC Status","gRPC Testing","Welcome to gRPC Python\u2019s documentation!"],titleterms:{admin:2,api:[3,10],asyncio:3,authent:1,author:1,block:3,callabl:[1,3],caveat:3,channel:[1,3],channelz:4,check:6,client:[1,3],code:[1,3],compress:1,connect:1,content:[1,2,3,4,5,6,7,8,9,10],context:[1,3],creat:[1,3],credenti:1,csd:5,document:10,exampl:7,except:[1,3],futur:1,glossari:0,grpc:[1,2,3,4,5,6,7,8,9,10],handler:1,health:6,indic:10,interceptor:[1,3],interfac:[1,3],local:1,metadata:3,method:1,modul:[1,2,3,4,5,6,7,8,9],multi:[1,3],object:[1,3],overview:3,pars:1,protobuf:1,python:10,readi:1,refer:10,reflect:7,rpc:1,runtim:1,s:10,server:[1,3],servic:1,share:[1,3],side:[1,3],statu:[1,8],tabl:10,test:9,type:1,version:1,welcom:10,what:[2,4,5,7]}})